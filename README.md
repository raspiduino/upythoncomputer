# MicroPython Computer
A MiniComputer based on Arduino, ESP8266 and MicroPython!
![alt](https://raw.githubusercontent.com/raspiduino/upythoncomputer/master/device_pic.jpg)

## Description
MicroPython provide a small shell to run Python codes and commands. Usually you have to connect to it through Serial Monitor or webRPEL. This project make that shell portable by bring it to Arduino with a Nokia 5110 LCD and 3 button as keyboard. With it, now you can make your MicroPython portable and bring it everywhere you want without bring any computer to connect.

## Instruction to setup

## Pins
Please connect like the picture below:
![alt](https://raw.githubusercontent.com/raspiduino/upythoncomputer/master/pinout.PNG)
<br /> This is the connect for the 5V nokia 5110 LCD. If you want to use with 3V ones, please connect 4.7 k resistor to the lcd like this:
![alt](https://raw.githubusercontent.com/raspiduino/upythoncomputer/master/pinout_res.PNG)
<br /> (A0 -> A5 is analog pin on your Arduino)
<br />To be smallest, please plug the LCD into Analog header like this:
![alt](https://raw.githubusercontent.com/raspiduino/upythoncomputer/master/plug_lcd.jpg)
