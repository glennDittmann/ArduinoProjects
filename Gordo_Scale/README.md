A scale we built for fun to measure food intake of our cat 🙀 :trollface:
---
It uses 
* an Arduino Uno (like) microcontroller 
* 1-2 load cells (wheatstone bridges)
* a wheatstone amplifier shield
* a LCD screen (with buttons) 
* additional stuff like female wires and stackable headers

Note that the following additionaly libraries are necessary
* the standard Arduino [LiquidCrystal library](https://www.arduino.cc/en/Reference/LiquidCrystal)
* the [wheatstone amplifier shield library](https://github.com/RobotShop/Wheatstone-Bridge-Amplifier-Shield)
* the [utility functions library](https://github.com/RobotShop/Wheatstone-Bridge-Amplifier-Shield/tree/master/Examples/strain_gauge_shield_and_lcd_arduino_uno_code) for easy communication between the components

The first one is preincluded in the ArduinoIDE. <br>
For the last two it would be sufficient to place the respective *\*.h*, *\*.cpp* files in an equally named folder in the libraries folder of your ArduinoIDE. <br>
Also we needed to adjust the utility functions library such that the button pressing was correctly done, i.e. change the upper bound voltages. 
Thanks to RobotShop for the [good tutorial](https://www.robotshop.com/community/tutorials/show/arduino-5-minute-tutorials-lesson-8-wheatstone-shield-amp-lcd) and the decent additional code.
