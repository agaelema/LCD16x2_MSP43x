# LCD16x2_MSP43x

A LCD HD44780 developed to MSP43x line with easy configuration

LCD 16x2 / 16x4 using 4bit mode - lcd16x2_msp43x.c
1. Developed focusing on the MSP430 and MSP432, but can be adapted to other hardwares (future feature)
2. Easy to configure and adapt in new projects (changing some #define in .h)
3. With configuration error detection (will show some error if something go wrong)
4. With simple conversion of integer and float to print on lcd
* I encourage you to use my "Embedded_Printf" to convert the number to string with more options

Default pins
* P1.0 > P1.3 - Data bus
* P1.6 - EN
* P1.7 - RS

To change Port and/or pins, change the value of #define inside the .h file.

Examples
* MSP430G2553
* MSP430FR2433


___
### DISCLAIMER

This software is provided 'as is' with no explicit or implied warranties in respect of its properties, including, but not limited to, correctness and/or fitness for purpose.
