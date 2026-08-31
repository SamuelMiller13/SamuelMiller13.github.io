---
title: "Syringe Pump"
excerpt: "This custom DIY syringe pump is capable of dispensing as little as 1uL/min of liquid, as well as up to 10mL/min."
header:
  image: ../assets/img/Syringe Pump Assembly Render.png
  teaser: ../assets/img/syringepumpphoto.jpg
gallery:
  - url: ../assets/img/Syringe Pump Assembly Render.png
    image_path: ../assets/img/Syringe Pump Assembly Render.png
    alt: "placeholder image 1"
  - url: ../assets/img/syringepumpphoto.jpg
    image_path: ../assets/img/syringepumpphoto.jpg
    alt: "placeholder image 2"


---

For our Rapid Prototyping capstone project, my team designed and built a fully functional syringe pump from the ground up — mechanical housing, electronics, and firmware all engineered in-house. The pump uses a NEMA 17 stepper motor driving a lead screw to precisely actuate a syringe plunger, delivering fluid at flow rates adjustable in 0.1 mL/min increments via a potentiometer, with real-time feedback on an LCD display.
{% include gallery caption="" %}
# The design operates as described below:
__The red center button:__ Acts as a power switch, turning the pump on and off.  
__The red outter buttons:__ Both left and right button's rotate the lead screw, driving the carriage fowards/backwards respectively.  
__The dial potentiometer:__ Acts as a speed variable dial, allowing the user to increase/decrease flow rate.  

## Off-the-Shelf Parts
| Part Name | Category |
|---|---|
| NEMA-17 Motor | Motor |
| Lead-Screw TR8x8x250mm | Motion |
| Nut-TR8x8-4 | Motion |
| LM8UU Linear Bearing | Motion |
| Linear-Rod 8mm x 200mm | Motion |
| F688ZZ Flanged Ball Bearing | Motion |
| Flexible Coupler | Motion |
| Lock-Collar-Linear-Rod | Motion |
| Lock-Collar-Lead-Screw | Motion |
| V-Slot 20x40x350 | Frame/Extrusion |
| Complete Limit Switch | Electronics |
| LCD16x2 Display | Electronics |
| LED | Electronics |
| Momentary Pushbutton | Electronics |
| Push Button 12mm | Electronics |
| Potentiometer | Electronics |
| 91290A117 Alloy Steel Socket Screw | Fastener |
| 91290A113 Alloy Steel Socket Screw | Fastener |
| 90128A244 Zinc-Plated Alloy Screw | Fastener |
| M3x8 Thread-Forming Screw | Fastener |
| M3x10mm Bolt | Fastener |
| Bolt + T-Nut | Fastener |
| 94459A180 Heat-Set Insert | Fastener |
| 94459A769 Heat-Set Insert | Fastener |
| Momentary Button Nut | Fastener |
| Syringe (10 mL) | Consumable |

## 3D Printed Parts
| Part Name | Function |
|---|---|
| Housing Base | Main enclosure base |
| Housing Lid (Updated) | Enclosure lid, mounts LCD/electronics |
| Motor-Mounting | Secures NEMA-17 motor to frame |
| End Support | Supports lead screw/rod end |
| End Support Holding Syringe | Holds syringe flange in place |
| Carriage | Mounts to lead screw, drives plunger |
| Clamp for Carriage | Secures syringe plunger head to carriage |

