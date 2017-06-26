LXRobotics P2 StackableMotorshield
==============

[![License: CC BY-NC-SA 4.0](https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg)](http://creativecommons.org/licenses/by-nc-sa/4.0/)

# Image

![LXRobotics P2 StackableMotorshield](https://raw.githubusercontent.com/lxrobotics/StackableMotorshield/master/images/stackable-motorshield-mulitple-small.JPG)

# Description

The Stackable Motorshield facilitates the control of up to 8 high power motors (18 V / 46 A) using only one Arduino Board. This can be achived by using the same amount of Stackable Motorshields as the amount of motors desired to be controlled. The communication between Motorshields and Arduino Board is done over the I2C-Interface. The address of each Stackable Motorshields can be configured. Inputs for connecting rotary encoders for determining the number of rotations of the motor are available on the shield. For a quick and easy start, a open source Arduino library with sample programs is available.

**Features**

* Control of up to 8 High Power Motors through stacking of up to 8 Stackable Motorshields on top of each other
* Voltage supply range: 7 to 18 Volts
* Can be used with 2S, 3S and 4S LiPo-battery
* High performance: Maximum continuous output 46 A
* Control via I2C -  only 2 Arduino-Pins are required (SDA = A4, SCL = A5)
* I2C-PullUp-resistors connectable through jumper
* Adjustable address through jumper
* Inputs for rotary encoders
* Motor drivers are protected against short circuit (to ground/supply), overheating, overvoltage and undervoltage
* Arduino Library with example programs is available on GitHub
* 2 Status-LEDs (Orange: User LED, Red: Active when speed of motor > 0)

# Video

[![VIDEO1](http://img.youtube.com/vi/2M2tKpRYI7Y/.jpg)](https://www.youtube.com/watch?v=2M2tKpRYI7Y "LXRobotics Stackable Motorshield")
