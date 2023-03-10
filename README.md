# ATMEGA1284_OLED_Gameboy

DIY gameboy powered from 9V battery, that can play three built-in games. </br>
</br>
Developed within University of Tartu Hardware Project course. </br>
Almost everything you can see I developed by myself: </br>
1. Schematic design + component selection
2. PCB design
3. 3D printed case, soldering, assembling
4. Firmware
5. Games

Used parts: </br>
1. [ SSD1306 OLED driver ](https://github.com/afiskon/stm32-ssd1306), ported for AVR MCU

#### Photos of board

Assembled board |  PCB | 3D printed case
:-------------------------:|:-------------------------:|:-------------------------:
<img src="/media/assembled.png" width="auto" height="auto"/></br>  |  <img src="/media/pcb.png" width="auto" height="auto"/></br> | <img src="/media/case.png" width="auto" height="auto"/></br> 

#### Demo videos (youtube)

[ Games ](https://www.youtube.com/watch?v=D_vLn6cdAP8&ab_channel=LeonidTsigrinski)
[ Debug ](https://www.youtube.com/watch?v=agJH_pz0l60&ab_channel=LeonidTsigrinski)

#### Schematics

[ PDF ](https://github.com/Leonid-98/ATMEGA1284_OLED_Gameboy/blob/main/media/schematic.pdf)


## Hardware overview

Very simple project from hardware side: </br>
1. Two power inputs
    - 5V USB with ESD protection
    - Battery input with 5V LDO (supporting 15V max)
2. USB to UART bridge
4. PWM controlled buzzer
5. 4 buttons
6. 2D joystick (potentiometer)
7. I2C OLED screen
8. Atmega1284-AUR programmed with JTAG
9. No XTAL, using internal oscillator

## Software overview

Atmega1284 is 8-bit AVR MCU, 8MHz FCPU, 128 KB Flash, 16 KB SRAM, 4 KB EEPROM. </br>
Most impact were done on code. It's bare metal application, no HAL. Implemented features:</br>
1. Plays music when game lost. Music can be[ changed ](https://github.com/robsoncouto/arduino-songs)
2. 

## 
