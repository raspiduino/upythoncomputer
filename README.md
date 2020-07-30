# MicroPython Computer
A MiniComputer based on Arduino, ESP8266 and MicroPython!
![alt](https://raw.githubusercontent.com/raspiduino/upythoncomputer/master/device_pic.jpg)

## Description
MicroPython provide a small shell to run Python codes and commands. Usually you have to connect to it through Serial Monitor or webRPEL. This project make that shell portable by bring it to Arduino with a Nokia 5110 LCD and 3 button as keyboard. With it, now you can make your MicroPython portable and bring it everywhere you want without bring any computer to connect.

## Setup
First, flash the esp8266 by connect like the picture:
![alt](https://raw.githubusercontent.com/raspiduino/upythoncomputer/master/flash_esp8266.PNG)
<br /> Remember to connect GPIO0 to GND and NOT VCC! Then follow these steps:
- Connect esp8266's RX pin to the USB to Serial device (search google for this if you don't have one) TX pin, and connect esp8266's TX pin to USB to Serial's RX pin, and plug the device to your computer
- Go to https://micropython.org/resources/firmware/esp8266-20191220-v1.12.bin and download the MicroPython .bin file (Please use this since it's stable). You also need esptool at https://github.com/espressif/esptool to flash it
- Open the Command prompt or Terminal and type in:
> esptool.py --port [your_COM_port] erase_flash
> esptool.py --port [your_COM_port] --baud 460800 write_flash --flash_size=detect 0 the_bin_file_name_and_path.bin
<br /> Replace it with yours.
- Unplug the USB to serial module and plug your Arduino in. Clone this git and build the code with Arduino IDE or you can also download the precompiled .hex file and flash it into your Arduino.
- Connect the pins like below:

## Pins
Please connect like the picture below:
![alt](https://raw.githubusercontent.com/raspiduino/upythoncomputer/master/pinout.PNG)
<br /> This is the connect for the 5V nokia 5110 LCD. If you want to use with 3V ones, please connect 4.7 k resistor to the lcd like this:
![alt](https://raw.githubusercontent.com/raspiduino/upythoncomputer/master/pinout_res.PNG)
<br /> (A0 -> A5 is analog pin on your Arduino)
<br />To be smallest, please plug the LCD into Analog header like this:
![alt](https://raw.githubusercontent.com/raspiduino/upythoncomputer/master/plug_lcd.jpg)

## Usuage
