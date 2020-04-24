/***************************************************************************************
 * LCD 16x2 / 16x4 using 4bit mode - lcd16x2_msp43x.c
 * - Developed focusing on the MSP430 and MSP432, but can be adapted to other hw
 * - Easy to configure and adapt in each new project (changing some #define in .h)
 * - with configuration error detection (will show some error if something go wrong)
 * - with simple conversion of integer and float to print on lcd
 * - - I encourage you to use my "Embedded_Printf" together (convert the number to string)
 *
 *  author: Haroldo Amaral - agaelema@gmail.com
 *  v0.2.1 - 2017/12/28
 ***************************************************************************************
 *  log:
 *    v0.1      . Initial version without configuration macros
 *    v0.2.1    + add macros to facilitate the configuration
 *              . update some functions
 *    v0.2.2    - Remove unused parts
 ***************************************************************************************/

#include "lcd16x2_msp43x.h"
#include <stdint.h>


/***************************************************************************************
 *                          MACROS - Do not change
 ***************************************************************************************/
#define     _SET_PIN(port, pin)     P ## port ## OUT |= BIT ## pin
#define     _CLEAR_PIN(port, pin)   P ## port ## OUT &= ~BIT ## pin

#define     _EN_SET(port, pin)      _SET_PIN(port, pin)
#define     EN_SET                  _EN_SET(_EN_PORT, _EN_PIN)          // macro to set EN pin
#define     _EN_CLEAR(port, pin)    _CLEAR_PIN(port, pin)
#define     EN_CLEAR                _EN_CLEAR(_EN_PORT, _EN_PIN)        // macro to clear EN pin

#define     _RS_SET(port, pin)      _SET_PIN(port, pin)
#define     RS_SET                  _RS_SET(_RS_PORT, _RS_PIN)          // macro to set RS pin
#define     _RS_CLEAR(port, pin)    _CLEAR_PIN(port, pin)
#define     RS_CLEAR                _RS_CLEAR(_RS_PORT, _RS_PIN)        // macro to clear RS pin

#define     _LCD_DATA_PORT(port)    P ## port ## OUT
#define     _LCD_DATA_OUT(port)     _LCD_DATA_PORT(port)
#define     LCD_DATA_OUT            _LCD_DATA_OUT(_LCD_4BIT_PORT)       // macro defining data port

#define     LCD_EN_STROBE           EN_CLEAR; EN_SET; EN_CLEAR;


/***************************************************************************************
 *
 ***************************************************************************************/
static void lcd16x2_Wait(volatile uint_fast16_t wait_1)
{
    volatile int wait_2;
    for (wait_1; wait_1>1; wait_1--)
    {
        for (wait_2 = 110; wait_2 >= 0; wait_2--);
    }
}


/***************************************************************************************
 *
 ***************************************************************************************/
void lcd16x2_Init(void)
{
    EN_CLEAR;
    RS_CLEAR;

    lcd16x2_Wait(1100);                                         // initialization delay - wait +- 15ms

    lcd16x2_Cmd(LCD_CMD_INIT_4BIT);                             // force 4bit mode after power up

    LCD_EN_STROBE;
    lcd16x2_Wait(150);
    LCD_EN_STROBE;
    lcd16x2_Wait(150);
    LCD_EN_STROBE;
    lcd16x2_Wait(150);

    lcd16x2_Cmd(LCD_CMD_RETURN_HOME);                           // move cursor to home
    LCD_EN_STROBE;

    lcd16x2_Wait(100);

    lcd16x2_Cmd(LCD_CMD_CLEAR_LCD);                             // clear display
    lcd16x2_Wait(100);

    lcd16x2_Cmd(LCD_CMD_2LINES_4BIT);                           // configure in 4bit mode 2 lines
    lcd16x2_Wait(100);

    lcd16x2_Cmd(LCD_CMD_DISPLAY_ON_CURSOR_ON);                  // display ON, cursor ON
    lcd16x2_Wait(100);

//    lcd16x2_Cmd(LCD_CMD_DISPLAY_ON_CURSOR_BLINK);               // display ON, cursor BLINK
//    lcd16x2_Wait(100);

    lcd16x2_Cmd(LCD_CMD_ENTRY_INCREMENT_SHIFT_OFF);             // increment address without shift
    lcd16x2_Wait(100);

    lcd16x2_Cmd(LCD_CMD_CURSOR_1ST_LINE);                       // put cursor at first line
    lcd16x2_Wait(100);
}


/***************************************************************************************
 *
 ***************************************************************************************/
void lcd16x2_Cmd(uint_fast8_t Data)
{
	RS_CLEAR;
	EN_CLEAR;

    LCD_DATA_OUT &= ~(_LCD_4BIT_HIGH << _LCD_DATA_BASE);                    // reset data pins
    LCD_DATA_OUT |= (((Data >> 4) & _LCD_4BIT_HIGH) << _LCD_DATA_BASE);     // send MSB first

	EN_SET;
	lcd16x2_Wait(6);
	EN_CLEAR;

	LCD_DATA_OUT &= ~(_LCD_4BIT_HIGH << _LCD_DATA_BASE);                    // reset data pins
	LCD_DATA_OUT |= (Data & _LCD_4BIT_HIGH) << _LCD_DATA_BASE;              // send the LSB

	EN_SET;
	lcd16x2_Wait(6);
	EN_CLEAR;
}


/***************************************************************************************
 *
 ***************************************************************************************/
void lcd16x2_Data(uint_fast8_t char_lcd)
{
    RS_SET;
    EN_CLEAR;

    LCD_DATA_OUT &= ~ (_LCD_4BIT_HIGH << _LCD_DATA_BASE);                   // reset data pins
    LCD_DATA_OUT |= (((char_lcd >> 4) & _LCD_4BIT_HIGH) << _LCD_DATA_BASE); // send MSB first

    EN_SET;
	lcd16x2_Wait(6);
	EN_CLEAR;

	LCD_DATA_OUT &= ~ (_LCD_4BIT_HIGH << _LCD_DATA_BASE);                   // reset data pins
	LCD_DATA_OUT |= ((char_lcd & _LCD_4BIT_HIGH) << _LCD_DATA_BASE);        // send LSB

	EN_SET;
	lcd16x2_Wait(6);
	EN_CLEAR;
}


/***************************************************************************************
 *
 ***************************************************************************************/
void lcd16x2_SetPosition(uint_fast8_t row, uint_fast8_t coll)
{
        if(row) coll |= 0x40;
        coll |=0x80;
        lcd16x2_Cmd(coll);
}


/***************************************************************************************
 *
 ***************************************************************************************/
void lcd16x2_PrintString(char *str)
{
	while (*str)                                            // while different of "\0"
	{
		lcd16x2_Data(*str);									// print the char
		str++;											    // increment pointer
	}
}


/*
 * versão muito limitada
 * - indicar o uso da embedded_printf
 * Converte um número inteiro para ser escrito no LCD de -9999 a 9999
 */
/***************************************************************************************
 *
 ***************************************************************************************/
void lcd16x2_PrintInt(volatile int_fast16_t iNumber)
{
    uint_fast8_t thousands, hundreds, tens, ones;

	if (iNumber < 0)
	{
	    lcd16x2_Data('-');
	    iNumber = iNumber * (-1);
	}

	thousands = iNumber / 1000;
	lcd16x2_Data(thousands + '0');                          // convert the number in ascii code

	hundreds = ((iNumber - thousands*1000)-1) / 100;
	lcd16x2_Data(hundreds + '0');                           // convert the number in ascii code

	tens = (iNumber % 100) / 10;
	lcd16x2_Data(tens + '0');                               // convert the number in ascii code

	ones = iNumber % 10;
	lcd16x2_Data(ones + '0');                               // convert the number in ascii code
}


/*
 * utiliza "car_float" como double para garantir que o número não seja arredondado
 * rotina atual aceita caracteres de -9999.9999 a 9999.9999
 */
/***************************************************************************************
 *
 ***************************************************************************************/
void lcd16x2_PrintFloat(volatile float var_float)
{
    int_fast16_t var_int;

    if (var_float < 0)                                      // if negative
    {
        var_float = var_float * (-1);                       // multiply by -1
        lcd16x2_Data('-');                                  // put minus symbol
    }

	var_int = (int_fast16_t) var_float;						// typecast - convert to integer
	lcd16x2_PrintInt(var_int);								// use integer function

	lcd16x2_Wait(2);
	lcd16x2_Data('.');										// write the dot "." - 0x2E

	var_float = (var_float - var_int)*10000;			    // multiply the residual
	var_int = (int_fast16_t) var_float;						// typecast - convert to integer
	lcd16x2_PrintInt(var_int);								// use integer function
}


/***************************************************************************************
 *
 ***************************************************************************************/
void lcd16x2_ShitftRigh(uint_fast8_t times)
{
    while(times > 0)
    {
        lcd16x2_Cmd(LCD_CMD_SHIFT_DISPLAY_RIGHT);
        lcd16x2_Wait(2);
        times--;
    }
}


/***************************************************************************************
 *
 ***************************************************************************************/
void lcd16x2_ShitftLeft(uint_fast8_t times)
{
    while(times)
    {
        lcd16x2_Cmd(LCD_CMD_SHIFT_DISPLAY_LEFT);
        lcd16x2_Wait(2);
        times--;
    }
}
