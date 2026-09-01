#include <AccelStepper.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/**
 * @file SyringePump.ino
 * @brief Arduino firmware for a syringe pump with potentiometer-controlled flow rate,
 * LCD feedback, limit switch protection, and manual jogging.
 */

// ========================== PIN DEFINITIONS ==========================

/** @brief Step pulse output pin for stepper driver */
const int STEP_PIN = 2;

/** @brief Direction control pin for stepper driver */
const int DIR_PIN = 3;

/** @brief Start/Stop button input pin */
const int BUTTON_PIN = 7;

/** @brief Limit switch input pin (detects syringe empty) */
const int LIMIT_SWITCH_PIN = 8;

/** @brief Manual jog forward button pin */
const int BUTTON_JOG_FORWARD_PIN = 4;

/** @brief Manual jog reverse button pin */
const int BUTTON_JOG_REVERSE_PIN = 5;

/** @brief Potentiometer analog input pin (flow rate control) */
const int POT_PIN = A0;

/** @brief Green status LED pin (running) */
const int LED_GREEN_PIN = 9;

/** @brief Blue LED pin (unused currently) */
const int LED_BLUE_PIN = 10;

/** @brief Red status LED pin (empty/error) */
const int LED_RED_PIN = 11;

// ========================== LCD CONFIGURATION ==========================

/**
 * @brief 16x2 I2C LCD instance at address 0x27
 */
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ========================== MOTOR & FLOW CONSTANTS ==========================

/** @brief Microstep multiplier of the stepper driver */
const float MICROSTEP_FACTOR = 16.0;

/** @brief Total steps per motor revolution (with microstepping) */
const float STEPS_PER_REV = 200.0 * MICROSTEP_FACTOR;

/** @brief Lead screw travel per revolution (mm) */
const float LEAD_MM_PER_REV = 2.0;

/** @brief Conversion factor: cubic millimeters per mL */
const float MILLIMETER_CUBE_PER_ML = 1000.0;

/** @brief Seconds in a minute */
const float SECONDS_PER_MINUTE = 60.0;

/** @brief Maximum flow rate allowed by potentiometer */
const float MAX_POT_FLOW_ML_MIN = 7.5;

// ========================== SYRINGE DIMENSIONS ==========================

/** @brief Plunger diameter (mm) for 10 mL syringe */
const float DIAMETER_10ML = 14.7;

/** @brief Plunger diameter (mm) for 20 mL syringe */
const float DIAMETER_20ML = 19.1;

// ========================== USER SETTINGS ==========================

/** @brief Selected syringe size (10 or 20 mL) */
const int SYRINGE_SIZE_ML = 20;

/** @brief Commanded flow rate in mL/min (controlled by potentiometer) */
float COMMANDED_FLOW_RATE_ML_MIN = 0.0;

// ========================== STATE TRACKING ==========================

/** @brief Total syringe capacity based on selected size */
const float TOTAL_SYRINGE_VOLUME_ML = (SYRINGE_SIZE_ML == 10) ? 10.0 : 20.0;

/** @brief Tracks total steps moved forward (volume dispensed) */
long currentPositionSteps = 0;

/** @brief Stepper driver object */
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

/** @brief Cached screw lead value */
const float LINEAR_MM_PER_REV = LEAD_MM_PER_REV;

/** @brief Calculated syringe diameter */
float CURRENT_SYRINGE_DIAMETER_MM = 0.0;

/** @brief Calculated syringe cross-sectional area */
float SYRINGE_AREA_MM2 = 0.0;

/** @brief Calculated motor speed in steps/sec */
float TARGET_STEPS_PER_SECOND = 0.0;

/** @brief Target motor speed used by stepper driver */
float targetStepsPerSec = 0.0;

/** @brief Pump running state */
bool pumpRunning = false;

/** @brief Empty syringe state */
bool pumpEmpty = false;

/** @brief Manual jogging speed */
const float JOG_SPEED_STEPS_PER_SEC = -1000.0;

// ========================== TIMING VARIABLES ==========================

/** @brief Last LCD refresh timestamp */
unsigned long lastDisplayUpdateTime = 0;

/** @brief LCD refresh interval (ms) */
const long displayUpdateInterval = 500;

/** @brief Last serial print timestamp */
unsigned long lastSerialUpdateTime = 0;

/** @brief Serial refresh interval (ms) */
const long serialUpdateInterval = 200;

// ========================== LED CONTROL ==========================

/**
 * @brief Turn LED to Green (Running state)
 */
void setLedGreen() {
  digitalWrite(LED_GREEN_PIN, HIGH);   // Turn green LED ON
  digitalWrite(LED_BLUE_PIN, LOW);     // Turn blue LED OFF
  digitalWrite(LED_RED_PIN, LOW);      // Turn red LED OFF
}

/**
 * @brief Turn LED to Yellow (Paused/Idle state)
 */
void setLedYellow() {
  digitalWrite(LED_GREEN_PIN, 190);   // Mix red + green to get yellow
  digitalWrite(LED_BLUE_PIN, 0);
  digitalWrite(LED_RED_PIN, 255);
}

/**
 * @brief Turn LED to Red (Error/Empty state)
 */
void setLedRed() {
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, LOW);
  digitalWrite(LED_RED_PIN, HIGH);
}

// ========================== MOTOR SPEED CALCULATION ==========================

/**
 * @brief Calculates motor steps per second based on syringe size and desired flow rate
 */
void calculateMotorSpeed() {

  // Select syringe diameter
  if (SYRINGE_SIZE_ML == 10) {
    CURRENT_SYRINGE_DIAMETER_MM = DIAMETER_10ML;
  } else if (SYRINGE_SIZE_ML == 20) {
    CURRENT_SYRINGE_DIAMETER_MM = DIAMETER_20ML;
  } else {
    CURRENT_SYRINGE_DIAMETER_MM = DIAMETER_20ML; // Default
  }

  // Calculate syringe plunger area
  SYRINGE_AREA_MM2 = PI * pow((CURRENT_SYRINGE_DIAMETER_MM / 2.0), 2.0);

  // Protect against divide by zero
  if (COMMANDED_FLOW_RATE_ML_MIN < 0.001) {
    TARGET_STEPS_PER_SECOND = 0.0;
  } else {

    // Convert flow rate to mm³/sec
    float flowVolume_mm3_sec = (COMMANDED_FLOW_RATE_ML_MIN * MILLIMETER_CUBE_PER_ML) / SECONDS_PER_MINUTE;

    // Calculate linear plunger velocity
    float linearVelocity_mm_sec = flowVolume_mm3_sec / SYRINGE_AREA_MM2;

    // Convert linear velocity to step rate
    TARGET_STEPS_PER_SECOND = (linearVelocity_mm_sec / LINEAR_MM_PER_REV) * STEPS_PER_REV;
  }

  // Store target speed
  targetStepsPerSec = -TARGET_STEPS_PER_SECOND;
}

// ========================== POTENTIOMETER HANDLING ==========================

/**
 * @brief Reads potentiometer and maps it to flow rate in 0.1 mL/min steps
 */
void readFlowRatePot() {

  int potValue = analogRead(POT_PIN);          // Read raw ADC value

  float rawFlow = ((float)potValue / 1023.0) * MAX_POT_FLOW_ML_MIN;

  COMMANDED_FLOW_RATE_ML_MIN = round(rawFlow * 10.0) / 10.0; // Quantize to 0.1 steps

  if (COMMANDED_FLOW_RATE_ML_MIN < 0.0) {
    COMMANDED_FLOW_RATE_ML_MIN = 0.0;          // Clamp to zero
  }
}

// ========================== VOLUME & TIME ==========================

/**
 * @brief Calculates volume dispensed per motor step
 * @return volume per step in mL
 */
float calculateVolumePerStep() {

  float volumePerRev_mm3 = SYRINGE_AREA_MM2 * LINEAR_MM_PER_REV;   // Volume per screw rev
  float volumePerStep_mL = (volumePerRev_mm3 / STEPS_PER_REV) / MILLIMETER_CUBE_PER_ML;

  return volumePerStep_mL;
}

/**
 * @brief Updates remaining time and LCD display
 * @param flowRate_mL_min Current flow rate
 */
void updateTimeRemaining(float flowRate_mL_min) {

  currentPositionSteps = abs(stepper.currentPosition()); 

  // The rest of the calculation naturally yields positive results:
  float volumePerStep_mL = calculateVolumePerStep();

  // volumeDispensed_mL will be positive because currentPositionSteps is positive
  float volumeDispensed_mL = currentPositionSteps * volumePerStep_mL;

  // volumeRemaining_mL will be positive as long as volumeDispensed_mL < TOTAL_SYRINGE_VOLUME_ML
  float volumeRemaining_mL = TOTAL_SYRINGE_VOLUME_ML - volumeDispensed_mL;

  float timeRemaining_sec;

  if (flowRate_mL_min > 0.001 && volumeRemaining_mL > 0) {
    timeRemaining_sec = (volumeRemaining_mL / flowRate_mL_min) * SECONDS_PER_MINUTE;
  } else {
    timeRemaining_sec = 0.0;
  }

  int totalSeconds = (int)timeRemaining_sec;
  int minutes = totalSeconds / (int)SECONDS_PER_MINUTE;
  int seconds = totalSeconds % (int)SECONDS_PER_MINUTE;

  char timeBuffer[25];
  
  // 

  // ----- LCD Row 1 -----
  lcd.setCursor(0, 0);
  lcd.print("Flow:");
  lcd.print(COMMANDED_FLOW_RATE_ML_MIN, 1);
  lcd.print("mL/min  "); // Added space for alignment

  // ----- LCD Row 2 -----
  lcd.setCursor(0, 1);
  if (pumpEmpty || volumeRemaining_mL <= 0.0) {
    lcd.print("Status: EMPTY!  "); // Added space for alignment
  } else {
    sprintf(timeBuffer, "Time: %dm %02ds   ", minutes, seconds); // Added spaces for alignment
    lcd.print(timeBuffer);
  }
}

// ========================== MOTOR CONTROL ==========================

/**
 * @brief Starts the motor at given speed
 */
void startMotor(float steps_per_sec) {
  setLedGreen();
  stepper.setSpeed(steps_per_sec);
  pumpRunning = true;
}

/**
 * @brief Stops the motor (non-empty state)
 */
void stopMotor() {
  if (!pumpEmpty) {
    setLedYellow();
  }

  stepper.setSpeed(0.0);
  pumpRunning = false;
  stepper.setSpeed(0.0);
}

/**
 * @brief Stops motor and marks syringe as empty
 */
void stopMotorEmpty() {
  setLedRed();
  stepper.setSpeed(0.0);
  pumpRunning = false;
  pumpEmpty = true;

  lcd.setCursor(0, 1);
  lcd.print("Status: EMPTY!  ");
}

// ========================== INPUT HANDLING ==========================

/**
 * @brief Checks limit switch state
 */
void checkLimitSwitch() {
  int limitSwitchState = digitalRead(LIMIT_SWITCH_PIN);

  if (limitSwitchState == HIGH) {
    stopMotorEmpty();
  }
}

/**
 * @brief Handles main start/stop button logic
 */
void checkButtonState() {

  if (pumpEmpty) {
    return;
  }

  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && !pumpRunning) {
    calculateMotorSpeed();
    startMotor(targetStepsPerSec);
  }
  else if (buttonState == HIGH && pumpRunning) {
    stopMotor();
  }
}

/**
 * @brief Handles manual jog forward and reverse buttons
 */
void checkJogButtons() {

  if (pumpRunning) {
    return;
  }

  // Forward jog
  if (digitalRead(BUTTON_JOG_FORWARD_PIN) == LOW) {

    if (digitalRead(LIMIT_SWITCH_PIN) == LOW) {
      setLedYellow();
      stepper.setSpeed(JOG_SPEED_STEPS_PER_SEC);
    } else {
      stopMotorEmpty();
    }
  }

  // Reverse jog
  else if (digitalRead(BUTTON_JOG_REVERSE_PIN) == LOW) {

    currentPositionSteps = 0;
    stepper.setCurrentPosition(0);

    if (pumpEmpty) {
      pumpEmpty = false;
    }

    setLedYellow();
    stepper.setSpeed(-JOG_SPEED_STEPS_PER_SEC);
  }

  // No jog pressed
  else {
    stopMotor();
  }
}

// ========================== SETUP ==========================

/**
 * @brief Arduino setup routine
 */
void setup() {

  Serial.begin(9600);
  Serial.println("Starting Pump with Potentiometer Control...");

  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);
  pinMode(BUTTON_JOG_FORWARD_PIN, INPUT_PULLUP);
  pinMode(BUTTON_JOG_REVERSE_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.print("Syringe Pump V2.0");
  lcd.setCursor(0, 1);
  lcd.print("Reading Pot...");

  readFlowRatePot();
  calculateMotorSpeed();

  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(500.0);

  currentPositionSteps = 0;
  stepper.setCurrentPosition(0);

  stopMotor();
}

// ========================== MAIN LOOP ==========================

/**
 * @brief Main program loop
 */
void loop() {

  readFlowRatePot();       // Update flow rate from potentiometer

  if (pumpRunning) {
    calculateMotorSpeed(); // Recalculate speed on-the-fly

    if (stepper.speed() != targetStepsPerSec) {
      stepper.setSpeed(targetStepsPerSec);
    }
  }

  checkLimitSwitch();      // Check for syringe empty
  checkButtonState();      // Read main control button
  checkJogButtons();       // Read jog buttons

  stepper.runSpeed();      // Drive motor

  // LCD update
  if (millis() - lastDisplayUpdateTime >= displayUpdateInterval) {
    updateTimeRemaining(COMMANDED_FLOW_RATE_ML_MIN);
    lastDisplayUpdateTime = millis();
  }

  // Serial debug output
  if (millis() - lastSerialUpdateTime >= serialUpdateInterval) {
    Serial.print("Flow Rate: ");
    Serial.print(COMMANDED_FLOW_RATE_ML_MIN, 1);
    Serial.println(" mL/min");
    lastSerialUpdateTime = millis();
  }
}
