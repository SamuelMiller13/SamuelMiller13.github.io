---
title: "Multi-Material Pliers"
excerpt: "These pliers made from PLA and TPU are rigid, precise, and great at picking things up!"
header:
  image: ../assets/img/Syringe Pump Render Light Blue.png
  teaser: ../assets/img/Pliers-Angle.jpeg
gallery:
  - url: ../assets/img/Syringe Pump Render Light Blue.png
    image_path: ../assets/img/Syringe Pump Render Light Blue.png
    alt: "placeholder image 1"
  - url: ../assets/img/syringepumpphoto.jpg
    image_path: ../assets/img/Pliers-Overhead.jpeg
    alt: "placeholder image 2"


---

__Project Description__

For our Additive and Polymer-Based Manufacturing class project, I designed and built a set of fully functional print-in-place pliers that use a TPU leaf spring to control opening and closing, requiring no post-print assembly. The pliers' rigid handles and jaws are printed in PLA, while a flexible TPU leaf spring is printed directly into the pivot joint in the same build, providing the return force that automatically reopens the jaws after each squeeze. Because the spring element is generated in place rather than fastened on afterward, the design eliminates a separate metal spring, fastener, or manual assembly step entirely.

__Print-in-Place Design__

Print-in-place is an FDM design approach where a mechanism's moving parts — hinges, joints, springs, or linkages — are printed pre-assembled directly on the build plate, using small calibrated gaps (or, in multi-material designs, different filaments at the interface) so the parts can move relative to each other the moment printing finishes. It removes the labor, tolerancing, and failure points that come with post-print assembly, at the cost of requiring careful control over layer height, clearance, and cooling to keep moving surfaces from fusing together.
{% include gallery caption="" %}
# The design operates as described below:
__The red center button:__ Acts as a power switch, turning the pump on and off.  
__The red outter buttons:__ Both left and right button's rotate the lead screw, driving the carriage fowards/backwards respectively.  
__The dial potentiometer:__ Acts as a speed variable dial, allowing the user to increase/decrease flow rate.  

## Fusion Model
<iframe src="https://vanderbilt643.autodesk360.com/shares/public/SH90d2dQT28d5b602811ca2115866303006e?mode=embed" width="640" height="480" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true"  frameborder="0"></iframe>

[View Arduino Source Code](https://github.com/SamuelMiller13/SamuelMiller13.github.io/blob/main/SyringePump.ino)

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
