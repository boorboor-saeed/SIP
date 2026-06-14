# SIP

<p align="center">
SIP++  Semiconductor Ion Pulse Simulator (C++ Engine)
</p>

<p align="center">
<img width="270" height="270" alt="image" src="https://github.com/user-attachments/assets/9e8bed4f-59a6-41f8-816e-7548f3cefcf4" />
</p>

## Project Manifesto
SIP++ is a high‑performance simulation framework for modeling how signals form in silicon semiconductor detectors during heavy‑ion irradiation. It combines GEANT4 particle tracking with a custom charge‑transport engine that uses adaptive mesh refinement around dense ion tracks. This allows accurate simulation of plasma effects, electric‑field evolution, and signal formation in depleted and over‑depleted planar silicon detectors. Overall, SIP++ connects the initial energy deposition from particle interactions to the final digitized electronic signal, reproducing key features of experimentally observed waveforms.

## Core Features
*	Heavy Ion Dynamics: Modeling of high-density charge tracks and plasma column effects.
*	Adaptive nested mesh: Optimizes computation performance by fining the mesh around the plasma.
*	Transient Solver: Calculation of charge carrier transport (electrons and holes).
*	C++ Efficiency: Optimized for speed, allowing for large-scale Monte Carlo integration.

## Dependencies
1.	ROOT\
The CERN-developed ROOT library is utilized for plotting, visualization, and file management functionalities.
2.	Garfield++\
Garfield++ is required to obtain physical data related to charge carrier transport, including parameters such as mobility.
3.	GEANT4\
GEANT4 is employed to simulate primary ion tracks and to compute the spatial distribution of energy deposited within the detector’s active region.

# Reference
S. Boorboor, et al, "Efficient modeling of plasma effect on the signal formation in planar silicon detectors," The European Physical Journal C, vol. 85, p. 1281, 2025/11/10 2025.
https://link.springer.com/article/10.1140/epjc/s10052-025-14934-z
