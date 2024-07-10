# Loop Simulator for Automatic Control

The project was created for the Object Oriented Programming course at the Silesian University of Technology.

## Description

The project was written in C++ and uses the JSON for Modern C++ version 3.11.2 library (https://github.com/nlohmann/json/releases/tag/v3.11.2). 
The main objective of the project was to enable the simulation of systems with loops, ARX models, PID controllers and static objects together with the input signal. The input signal could be any set of signals: step, rectangular, triangular, sinusoidal and white noise.
The project provides the ability to simulate a variety of models stored in json format, easily modify the structure of loops, signals and write to a json file.

The code does not include protection against incorrect data entry.
The interface is only available in Polish.

## Installation instructions

A C++ compiler supporting the C++17 standard is required for the program to run.
Below are instructions on how to run a project with MinGW (for Windows).

**In the case of Windows:**

1. Clone the repository: `git clone https://github.com/VanitasMarcin/Loop_Simulator`
2. Go to the project directory: `cd project-name`
3. In a terminal, run the file `run_simulation.bat`
4. Enter `program`

**In the case of Linux:**
1. Clone the repository: `git clone https://github.com/VanitasMarcin/Loop_Simulator`
2. Go to the project directory: `cd project-name`
3. Grant permission to execute `the build.sh` file: `chmod +x build.sh`
4. In a terminal, run the file `run_simulation.sh`
5. Enter `program`
\
## Simulation parameters

 - **Sampling period** (double)
 - **Number of probes** (int)

## Signals parameters

The signals parameters are given in the order in which they are modified in the program. All parameters are variables of type double.

- **Base signal** - may not be modified
- **Step signal** - amplitude, start, finish
- **Rectangular signal** - amplitude, frequency, sampling period, duty cycle, start, finish
- **Triangular signal** - amplitude, frequency, sampling period, duty cycle, start, finish
- **Sinusoidal signal** - amplitude, frequency, sampling period, duty cycle, start, finish 
- **White noise** - mean, variance, start, finish

## Objects parameters

The objects parameters are given in the order in which they are modified in the program. 

- **Loop** - structure **(string)** (close or open)
- **PID controller** - gain factor **(double)**, integration time **(double)**, derivative time **(double)** 
- **ARX Model** - denominator coefficients **(vector of doubles)**, numerator coefficients **(vector of doubles)**, delay **(int)**, standard deviation **(double)**
- **Static object** - lower saturation **(double)**, upper saturation **(double)**

A space is used to separate the values. The end of a value entry in a vector shall be terminated by a semicolon.

## Authors

- VanitasMarcin

## License

This project is made available under the MIT license. Please see the LICENSE file for more information.


