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

Most impact were done on code. It's bare metal application, no HAL. Implemented features:</br>
1. Can play three different games: Dino (Google Chrome no inet), Pong and Snake
2. Plays music when game over. Music can be[ changed ](https://github.com/robsoncouto/arduino-songs)
3. Stores score into EEPROM
4. Score can be cleared in-game

Project structure contains few different folders:
1. `Common` contains code for peripheral devices (buzzer, joystick...)
2. `Core` contains MCU related code (ADC, Timer, I2C...)
3. `Drivers` contains only one driver - SSD1306 OLED driver
4. `Games` contains everything related to the gameplay, score calculating, generic bitmaps drawing etc...

## Game overview

When turning device on, user can see main menu processed in the main loop.
When user selects game, each game handles it's gameloop. </br>
During the game, score is calculated easy way: IT timer ticker counts how many ticks done. If user reached highest score, it's being stored into EEPROM and shown in the main menu. </br>
If game ends, user can continue the game or get back into main menu. </br>
in the main menu, there's additional `Debug` game, where user can see joystick movements, buttons response. There also possible to clear EEPROM score. </br>

## What would I do differently next time?

#### Use ARM MCU
Using AVR in the first place was mistake, because most AVR application in the web advertise Arduino framework. </br>
If I would use ARM chip, it would be easier to write game logic within RTOS. Also, I'd spent less time on HAL stuff, like I2C. </br>
Also, performance would be higher, input lag would be less visible

#### Use SPI instead of I2C
Since input lag is visible, going over 400 kHz limit would increase user experience

#### Use chip with direct USB support
For programming I used JTAG, that requires expensive programmer and additional wiring. </br>
Also, UART boot requires bootloader, that I don't have. Having  direct `D+` `D-` connections would make my life much easier.

#### Make PCB smaller
PCB is big relatively to OLED, also joystick in current setup feels like a third wheel. In the future, I would go with more compact design.



