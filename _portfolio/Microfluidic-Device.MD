
---
title: "Multi-Material Pliers"
excerpt: "This device is was made from PDMS in a clear VPP resin mold."
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

# Enhanced Pinched Flow Fractionation (EPFF) Microfluidic Device

This project focuses on designing a resin-printed microfluidic device capable of continuously separating small particles by size using enhanced pinched flow fractionation (EPFF). The device incorporates a narrow pinching channel, an expanded separation region, a snake-like flow-resistance structure, and three collection outlets. The primary design objective was to improve particle separation while maintaining reliable flow distribution and minimizing particle collisions.

## Introduction

**Pinched flow fractionation (PFF)** is a passive microfluidic separation technique that uses laminar fluid flow to separate suspended particles according to their diameters. The process begins when a particle-containing fluid enters a narrow channel alongside a particle-free buffer fluid. The buffer pushes particles toward one channel wall, causing their centers to occupy different positions based on particle size. Smaller particles travel closer to the wall, while larger particles remain farther away because their centers cannot approach the wall more closely than their radii. When the fluid enters a wider channel, these small positional differences are amplified as the streamlines spread apart, allowing particles to be collected through separate outlets.

**Enhanced pinched flow fractionation (EPFF)** improves this process by modifying the geometry and hydraulic resistance of the downstream channels. In this design, a snake-like structure and an asymmetric flow path control how fluid distributes between the separation and buffer regions. By directing more flow through the desired region, the design aims to increase the spacing between particle trajectories without requiring additional external separation forces.

One important application is the separation of polymer microparticles used in laboratory analysis and particle-size characterization. Conventional filters use physical openings to retain particles above a certain size, which can cause clogging, particle accumulation, and interrupted operation. In contrast, PFF continuously separates particles through controlled fluid motion without relying on a filter membrane. This makes it useful for processing particle suspensions where continuous operation and preservation of the collected particles are important.

Yamada et al. (2004) experimentally demonstrated continuous separation of polymer microbeads using PFF. Later, Vig and Kristensen (2008) investigated geometric modifications that increase particle separation distances, providing a foundation for this enhanced design.

**Primary Literature:**

- [Yamada, Nakashima, and Seki (2004), *Pinched Flow Fractionation: Continuous Size Separation of Particles Utilizing a Laminar Flow Profile in a Pinched Microchannel*](https://doi.org/10.1021/ac049863r)
- [Vig and Kristensen (2008), *Separation Enhancement in Pinched Flow Fractionation*](https://doi.org/10.1063/1.3028652)

## Design

The device was designed within a 25 × 75 mm footprint, with a 3 mm perimeter margin and an available channel width of approximately 19 mm. The pinched section was designed with a width of 0.60 mm and a length of 3 mm, followed by a broader region that allows particles to spread along distinct streamlines.

Outlet placement was determined by the expected particle trajectories after expansion. Because the particles are focused against the upper wall, the smallest particles remain closest to that wall, while the larger particles follow trajectories farther into the channel. Consequently, the upper outlet collects smaller particles, the middle outlet collects larger particles, and the lower outlet removes the remaining buffer flow. The boundaries were positioned to capture these predicted particle bands while providing enough spacing to reduce cross-contamination between outlets.

The snake-like structure was incorporated to adjust the hydraulic resistance of the downstream flow paths, improving the distribution of fluid through the enhanced separation region. Its geometry was selected to balance increased separation with the need to prevent excessive resistance and preserve adequate particle clearance.

The narrow enhanced region was set to approximately 3.5 mm wide and 10 mm long, with an adjacent wider region measuring 12 mm by 7.5 mm. The 3.5 mm entrance also provided approximately 1.05 mm of clearance beyond the predicted outermost particle trajectory, reducing the possibility of particle-wall collisions.

Using a simplified hydraulic-resistance model, the design produced a predicted separation enhancement factor of approximately 1.71, representing a theoretical 71% increase in particle spacing compared with the baseline conventional PFF geometry. This is a theoretical estimate rather than an experimentally verified separation improvement.

### Key Design Parameters

| Parameter | Dimension |
|---|---|
| Device footprint | 25 × 75 mm |
| Channel depth | 0.30 mm |
| Pinched channel | 0.60 × 3 mm |
| Broad separation width | 19 mm |
| Pinch-to-snake distance | 8 mm |
| Narrow enhanced segment | 3.5 × 10 mm |
| Wide enhanced segment | 12 × 7.5 mm |
| Snake/divider width | 1.5 mm |
| Predicted separation enhancement factor | 1.71 |

The enhanced separation factor was estimated using the ratio of outlet hydraulic resistances and the relative widths of the separation channels. For a rectangular microchannel, hydraulic resistance can be approximated by:

$$
R \approx \frac{12\mu L}{wh^3(1-0.63h/w)}
$$

where $\mu$ is dynamic viscosity, $L$ is channel length, $w$ is channel width, and $h$ is channel depth. This relationship shows that increasing channel length or decreasing channel width increases resistance, allowing the snake-like geometry to influence downstream flow distribution.

The separation enhancement factor is defined as:

$$
SEF = \frac{\Delta y_{\text{enhanced}}}{\Delta y_{\text{conventional}}}
$$

where $\Delta y$ represents the distance between the trajectories of differently sized particles at equivalent downstream measurement locations.

For the theoretical design:

$$
SEF = 1.71
$$

This corresponds to a predicted 71% increase in particle spacing relative to conventional PFF under comparable flow conditions.

## Instructions

The following procedure outlines the major steps for manufacturing the device using resin-based 3D printing.

1. **CAD Modeling:** Create the device geometry in SolidWorks, including the inlet channels, pinched section, expanded separation region, snake-like structure, and collection outlets.
2. **Prepare the Print:** Export the CAD model as an STL file and import it into slicing software. Orient the device to minimize unsupported features and preserve the accuracy of the small channels.
3. **Resin Printing:** Print the device mold using a high-resolution resin-printing process, such as SLA, with appropriate exposure and layer-height settings.
4. **Cleaning and Curing:** Remove uncured resin using a compatible cleaning solution and complete post-curing according to the resin manufacturer's instructions.
5. **PDMS Casting:** Pour degassed PDMS over the printed mold, cure the elastomer, and carefully remove the resulting microfluidic structure.
6. **Device Assembly:** Create inlet and outlet access holes, then bond the PDMS structure to a clean glass slide to seal the channels.
7. **Testing:** Introduce buffer fluid to check for leakage and blockages, then introduce a particle suspension and observe whether the particles follow the intended separation paths.

## Discussion

### Why Use Resin Printing?

Resin printing was selected primarily because of its ability to produce detailed geometries with relatively high dimensional accuracy while remaining accessible and cost-effective for rapid prototyping. Compared with fused filament fabrication (FFF), resin printing generally produces finer features and smoother channel surfaces, which are particularly important for maintaining consistent laminar flow. It also enables relatively quick adjustments to the CAD geometry without requiring new molds or specialized tooling.

Compared with traditional photolithography and soft lithography, resin printing can reduce fabrication complexity for prototype devices. It allows designers to directly translate CAD models into physical molds, making it easier to test alternative channel geometries. However, resin printing also introduces limitations, including surface roughness, dimensional inaccuracies, and possible PDMS curing inhibition from residual resin components. These limitations must be considered when designing devices intended to separate very small particles.

### Scaling and Future Improvements

The device could be modified to separate a wider range of particle sizes by adjusting the pinched channel width, expansion ratio, flow-rate ratio, and outlet positions. Smaller particles generally require more precise channel dimensions and greater separation amplification, while larger particles may require wider channels to prevent clogging. Adjusting the snake-like structure would also provide another method of controlling hydraulic resistance and improving separation efficiency.

For higher throughput, multiple identical separation channels could be arranged in parallel, allowing more fluid to be processed without dramatically increasing the flow velocity in each individual channel. Additional outlets could also be incorporated to collect more than two particle-size groups.

A useful next step would be to run computational fluid dynamics (CFD) simulations to evaluate fluid streamlines and particle trajectories. These results could be used to further optimize the outlet boundaries and resistance distribution before experimentally testing the device.

### What Determines the Minimum Particle Size?

The minimum particle size that can be reliably separated using PFF depends on several physical and manufacturing factors. **Channel-wall roughness** is especially important because the separation mechanism depends on small differences in particle-center positions near the wall. If the roughness is comparable to the particle diameter, it becomes difficult to maintain consistent particle trajectories.

Other limitations include Brownian motion, the difference in diameter between the particles being separated, channel dimensional accuracy, and the stability of the inlet flow rates. As particles become smaller, random diffusion becomes increasingly important relative to deterministic size-based positioning. Additionally, particles with very similar diameters may follow nearly identical trajectories, making them difficult to collect separately.

Improving the manufacturing resolution, maintaining stable flow conditions, and minimizing surface roughness would therefore be necessary to extend the device toward smaller particle sizes.

## References

1. Yamada, M., Nakashima, M., & Seki, M. (2004). [Pinched Flow Fractionation: Continuous Size Separation of Particles Utilizing a Laminar Flow Profile in a Pinched Microchannel](https://doi.org/10.1021/ac049863r). *Analytical Chemistry*.
2. Vig, A. L., & Kristensen, A. (2008). [Separation Enhancement in Pinched Flow Fractionation](https://doi.org/10.1063/1.3028652). *Applied Physics Letters*.
