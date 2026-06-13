***********************************************************************************************************************************************************************
The benchmark set offers a comprehensive evaluation of SIP++ across a wide spectrum of ions, ranging from alpha particles to titanium, with incident energies 
spanning from 5.5 MeV to 910 MeV. It also covers diverse detector conditions, including five planar silicon detectors under both front-side and rear-side irradiation.
***********************************************************************************************************************************************************************
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

<<<<<<Benchmark 1>>>>>>
Reference: R. N. Williams and E. M. Lawson, “The plasma effect in silicon semiconductor radiation detectors,” Nuclear Instruments and Methods, vol. 120, pp. 261–268, 1974.

Description: This benchmark examines the incidence of 5.5 MeV alpha particles on both the front and rear sides of three different detectors.
It includes simulations of DetA, DetB, and DetC, corresponding to Detectors 1, 6, and 7 in the experiment.


<<<<<<Benchmark 2>>>>>>
Reference: H. Hamrita, E. Rauly, Y. Blumenfeld, B. Borderie, M. Chabot, P. Edelbruck, et al., “Charge and current-sensitive preamplifiers for pulse shape discrimination
techniques with silicon detectors,” Nuclear Instruments and Methods in Physics Research Section A, vol. 531, pp. 607–615, 2004.

Description: This benchmark focuses on the incidence of 80 MeV carbon ions on the rear side of a detector. It includes the simulation of DetD.



<<<<<<Benchmark 3>>>>>>
Reference: N. Le Neindre, R. Bougault, S. Barlini, E. Bonnet, B. Borderie, G. Casini, et al., “Comparison of charged particle identification using pulse shape discrimination
and ΔE−E methods between front and rear side injection in silicon detectors,” Nuclear Instruments and Methods in Physics Research Section A, vol. 701, pp. 145–152, 2013.

Description: This benchmark investigates the incidence of various heavy ions on both the front and rear sides of a detector. It includes simulations of DetE under multiple incident
conditions.

<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

<<<<<<Note>>>>>>>>
Since SIP++ calculates the intrinsic current generated solely by electron–hole motion, the influence of the external readout circuitry is not included in
the simulation itself and must be treated separately.

To account for these effects, appropriate signal‑processing tools are provided in the PostAnalysis program. These tools model the electronics response and
convert the simulated intrinsic signal into a waveform comparable to that recorded by a laboratory digitizer.

Within the PostAnalysis program, three benchmark classes are implemented to process the signals and compare them with the corresponding experimental waveforms.
