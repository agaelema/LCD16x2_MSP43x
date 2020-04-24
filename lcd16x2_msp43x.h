/***************************************************************************************
 * LCD 16x2 / 16x4 using 4bit mode - lcd16x2_msp43x.h
 * - Developed focusing on the MSP430 and MSP432, but can be adapted to other hw
 * - Easy to configure and adapt in each new project (changing some #define in .h)
 * - with configuration error detection (will show some error if something go wrong)
 * - with simple conversion of integer and float to print on lcd
 * - - I encourage you to use my "Embedded_Printf" together (convert the number to string)
 *
 *  author: Haroldo Amaral - agaelema@gmail.com
 *  v0.2.2 - 2017/12/28
 ******************************************************************************
 *  log:
 *    v0.1      . Initial version without configuration macros
 *    v0.2.1    + add macros to facilitate the configuration
 *              . update some functions
 *    v0.2.2    - Remove unused parts
 ***************************************************************************************/

#ifndef _LCD16x2_msp43x_H_
#define _LCD16x2_msp43x_H_

#include <msp430.h>
#include <stdint.h>

/***************************************************************************************
 *          LCD PINS DEFINITION - will define PORT and PINS used by LCD
 ***************************************************************************************/
#define     _EN_PORT        1                   // default EN port - P1
#define     _EN_PIN         6                   // default EN pin  - P1.6
#define     _RS_PORT        1                   // default RS port - P1
#define     _RS_PIN         7                   // default RS pin  - P1.7

#define     _LCD_4BIT_PORT          1               // port used to data
#define     _LCD_DATA_BASE          0               // first low pin of 4 bit interface
#define     _LCD_4BIT_HIGH          0x0F            // 4 bits in high mode

/***************************************************************************************
 *                          CHEKCK CONFIGURATION RULES
 ***************************************************************************************/

/*
 * 4 bit mode need 4 bits (nibble) to transfer data
 * - verify if the 4 bits not extrapolated a byte size (normal port size)
 * - limitation of use 4 consecutive bits in a port (less overhead)
 */
#if     (_LCD_DATA_BASE > 4)
#error      "check configuration in .h - _LCD_DATA_BASE need be between 0 and 4 to not extrapolate 8 bits of PORT"
#endif

/*
 * check if the same port is used to RS and EN pin
 * - if yes, verify if they are sharing the same pin
 */
#if     (_EN_PORT == _RS_PORT) & (_EN_PIN == _RS_PIN)
#error      "Check configuration in .h - Same pin to RS and EN"
#endif

/*
 * verify if some pin is shared between lcd data port and EN pin
 */
#if     ((_EN_PORT == _LCD_4BIT_PORT) & (_EN_PIN >= _LCD_DATA_BASE) & ((_LCD_DATA_BASE+3) >= _EN_PIN))
#error      "Check configuration in .h - Sharing pins between DATA and EN"
#endif

/*
 * verify if some pin is shared between lcd data port and RS pin
 */
#if     ((_RS_PORT == _LCD_4BIT_PORT) & (_RS_PIN >= _LCD_DATA_BASE) & ((_LCD_DATA_BASE+3) >= _RS_PIN))
#error      "Check configuration in .h - Sharing pins between DATA and RS"
#endif


/***************************************************************************************
 *                                  LCD COMMAND LIST
 ***************************************************************************************/

#define     LCD_CMD_INIT_4BIT                       0x03    // initial value to change to 4bit mdoe
//#define     LCD_CMD_INIT_8BIT                       0x30    // initial value to change to 4bit mdoe

/*
 * ENTRY MODES
 * - entry data modes
 * http://www.dinceraydin.com/lcd/commands.htm
 */
#define     LCD_CMD_ENTRY_DECREMENT_SHIFT_OFF       0x04    // print char, decrement address - reverse order
#define     LCD_CMD_ENTRY_DECREMENT_SHIFT_ON        0x05    // print char, decrement address and shift right - reverse order
#define     LCD_CMD_ENTRY_INCREMENT_SHIFT_OFF       0x06    // print char and incrementaddress - normal order
#define     LCD_CMD_ENTRY_INCREMENT_SHIFT_ON        0x07    // print char, increment address and shift left - normal order

/*
 * OTHER COMMANDS
 * https://www.8051projects.net/lcd-interfacing/commands.php
 * http://www.firmcodes.com/microcontrollers/8051-3/interfacing-lcd-with-8051/lcd-commands-and-understanding-of-lcd/
 * https://mil.ufl.edu/3744/docs/lcdmanual/commands.html
 */
#define     LCD_CMD_CLEAR_LCD                       0x01
#define     LCD_CMD_RETURN_HOME                     0x02
#define     LCD_CMD_DISPLAY_OFF_CURSOR_OFF          0x08

#define     LCD_CMD_DISP_OFF_CURSOR_ON              0x0A
#define     LCD_CMD_DISPLAY_ON_CURSOR_OFF           0x0C
#define     LCD_CMD_DISPLAY_ON_CURSOR_ON            0x0E
#define     LCD_CMD_DISPLAY_ON_CURSOR_BLINK         0x0F

#define     LCD_CMD_MOVE_CURSOR_LEFT                0x10
#define     LCD_CMD_MOVE_CURSOR_RIGHT               0x14
#define     LCD_CMD_SHIFT_DISPLAY_LEFT              0x18
#define     LCD_CMD_SHIFT_DISPLAY_RIGHT             0x1C

#define     LCD_CMD_1LINE_4BIT                      0x20
#define     LCD_CMD_2LINES_4BIT                     0x28
//#define     LCD_CMD_1LINES_8BIT                     0x30
//#define     LCD_CMD_2LINES_8BIT                     0x38

#define     LCD_CMD_CURSOR_1ST_LINE                 0x80
#define     LCD_CMD_CURSOR_2ND_LINE                 0xC0
#define     LCD_CMD_CURSOR_3RD_LINE                 0x90
#define     LCD_CMD_CURSOR_4TH_LINE                 0xD0


/***************************************************************************************
 *                              PROTOTYPE OF FUNCTIONS
 ***************************************************************************************/

void lcd16x2_Init(void);

//void lcd16x2_Wait(volatile uint_fast16_t wait_1);

void lcd16x2_Cmd(uint_fast8_t Data);
void lcd16x2_Data(uint_fast8_t char_lcd);

//void lcd16x2_SetPosition(uint_fast8_t linha, uint_fast8_t coluna);
void lcd16x2_SetPosition(uint_fast8_t row, uint_fast8_t coll);

void lcd16x2_PrintString(char *str);
void lcd16x2_PrintInt(volatile int_fast16_t iNumber);
void lcd16x2_PrintFloat(volatile float var_float);

void lcd16x2_ShitftRigh(uint_fast8_t times);
void lcd16x2_ShitftLeft(uint_fast8_t times);

#endif /* _LCD16x2_msp43x_H_ */
