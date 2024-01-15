# Software, Firmware, and Hardware for a Battery Characterization System
Biological tags are very popular in the field of animal behaviour research.
These tags developers have to deal with numerous problems, both in hardware and software.
One of the problems is to choose the correct battery to put within the tag itself: the battery should be lightweight, to last long, to cope with different weather conditions, etc.
Until now, the setup and procedure of comparing different batteries performance included:
- A mocked tag: A dedicated circuit that used the battery in the same way the tag does
- The battery itself
- Scope and other expensive equipment to measure the voltage and current along time

This procedure is long, expensive and uncomfortable.
This project concentrates on biological tags that are put on birds, these tags send a short pulse (8-10ms) of location every ~1 second.

## Goal
This project implements an arduino and PC software that communicate with each other and make the entire procedure very easy, cheap and quick.
The project contains:
- Various arduino softwares for different needs
- A PC software (C#) that operates the arduino and logs the measurements
- A PC software (Python) for visualization

## Content

### Visualization
- createData.py: Creates a mock log file with mocked measurements
- visualizeData.py: Measurements visualization utility

### Measure
The C# project that operates the arduino, both for tag simulation and also with real tags.
In order to compile Measure.csproj to mono: 
- cd to Measure.csproj folder
- xbuild /p:TargetFrameworkVersion="v4.5"

#### AutoMeasureGraphMin
Arduino software to measure bio tags.
This software communicates with the PC software and sends the measurements to it.
Supports 2 modes:
- Simulation: The sofware simulates tag behaviour and measures the battery performance in pulses along time
- Real tag: Measurement of real tag pulses. This mode contains a pulse identification algorithm, becuase the tag itself produces the pulses.

#### AutoMeasureGraphStart
Arduino software to measure bio tags in a situation the tag fails to start.
This software records measurements as soon as it identifies an activity in the tag and sends it to the PC software

#### PCB
Circuit and printed-circut board design for the add-on analog board. These are Eagle 6.6 files. The "relabeled" schmatics is cleaned up a bit for clarity. It also does not include 0-Ohm resistors and jumper traces that are included in the original design to allow patching the board. 

#### Simulation
LTSpice simulation model for the analysis of the reservoir cap and its limiter resistor. 
