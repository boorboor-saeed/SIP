# SIP
SIP++  Semiconductor Ion Pulse Simulator (C++ Engine)

<img width="270" height="270" alt="image" src="https://github.com/user-attachments/assets/9e8bed4f-59a6-41f8-816e-7548f3cefcf4" />

# Project Manifesto
SIP++ is a high-performance computational framework designed to simulate the transient charge induction and pulse shape evolution in semiconductor detectors, specifically under heavy-ion irradiation. It bridges the gap between raw physical interaction (energy deposition) and the final digitized electronic signal.

# Core Features
•	Heavy Ion Dynamics: Modeling of high-density charge tracks and plasma column effects.bb
•	Adaptive nested mesh: Optimizes computation performance by fining mesh around the plasma.
•	Transient Solver: Calculation of charge carrier transport (electrons and holes).
•	C++ Efficiency: Optimized for speed, allowing for large-scale Monte Carlo integration.

# Dependencies
1.	ROOT
The CERN-developed ROOT library is utilized for plotting, visualization, and file management functionalities.
2.	Garfield++
Garfield++ is required to obtain physical data related to charge carrier transport, including parameters such as mobility.
3.	GEANT4
GEANT4 is employed to simulate primary ion tracks and to compute the spatial distribution of energy deposited within the detector’s active region.
