---
title: "Multi-Material Pliers"
excerpt: "These pliers made from PLA and TPU are rigid, precise, and great at picking things up!"
header:
  image: ../assets/img/Pliers-Banner.png
  teaser: ../assets/img/Pliers-Banner.png
gallery:
  - url: ../assets/img/Pliers-Banner.png
    image_path: ../assets/img/Pliers-Angle.jpeg
    alt: "placeholder image 1"
  - url: ../assets/img/Pliers-Angle.jpeg
    image_path: ../assets/img/Pliers-Overhead.jpeg
    alt: "placeholder image 2"


---

__Project Description__

For our Additive and Polymer-Based Manufacturing class project, I designed and built a set of fully functional print-in-place pliers that use a TPU leaf spring to control opening and closing, requiring no post-print assembly. The pliers' rigid handles and jaws are printed in PLA, while a flexible TPU leaf spring is printed directly into the pivot joint in the same build, providing the return force that automatically reopens the jaws after each squeeze. Because the spring element is generated in place rather than fastened on afterward, the design eliminates a separate metal spring, fastener, or manual assembly step entirely.

__Print-in-Place Design__

Print-in-place is an FDM design approach where a mechanism's moving parts — hinges, joints, springs, or linkages — are printed pre-assembled directly on the build plate, using small calibrated gaps (or, in multi-material designs, different filaments at the interface) so the parts can move relative to each other the moment printing finishes. It removes the labor, tolerancing, and failure points that come with post-print assembly, at the cost of requiring careful control over layer height, clearance, and cooling to keep moving surfaces from fusing together.
{% include gallery caption="" %}
# The design specs are described below:
__Jaw Length:__ 
__Jaw Width:__ 


## Fusion Model
<iframe src="https://vanderbilt643.autodesk360.com/shares/public/SH90d2dQT28d5b6028115263c5295bb9713a?mode=embed" width="640" height="480" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true"  frameborder="0"></iframe>

![First prototype of the print-in-place pliers](../assets/img/processed-4FB37C23-B030-4F64-A4B2-8C2A911B6702.jpeg)
*First prototype*

The first prototype confirmed that the print-in-place hinge and TPU leaf spring could be printed as a single piece without fusing, but it also showed a few issues I wanted to address in the next revision:

- **[e.g., spring was too stiff/too weak]** — the jaws [didn't fully close / snapped back too aggressively], so I planned to adjust the TPU leaf spring's thickness and length to tune the return force.
- **[e.g., pivot clearance]** — the joint gap was [too tight and bound up / too loose and had play], so the next version needed a revised clearance tolerance.
- **[e.g., jaw geometry]** — [describe fit/grip issue], which meant reshaping the jaw profile.

Update those bracketed points with what actually happened on your first print — happy to help you word the specifics once you tell me what went wrong.

## 3D Printed Parts

| Part Name | Material |
|---|---|
| Leaf-Spring | TPU |
| Plier-Arm-Female | PLA |
| Plier-Arm-Male | PLA |
| Lock-Key | PLA |

