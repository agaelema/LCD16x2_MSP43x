/***************************************************************************************
 * Example project of "lcd16x2_msp43x" library
 *
 * Use the following pins
 * - P1.0 - P1.4    = 4 bit data line
 * - P1.6           = EN pin
 * - P1.7           = RS pin
 *
 * configuration of pins/port can be modified in the .h file
 *
 * author: Haroldo Amaral - agaelema@globo.com
 * 2017/12/28
 ***************************************************************************************/

#include <msp430.h>
#include <stdint.h>
#include "lcd16x2_msp43x.h"

double f;
uint16_t counter = 0;

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                               // stop watchdog
	PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

	P1DIR = 0xFF;									        // P1 as output
	P1OUT = 0x00;									        // reset all pins

	lcd16x2_Init();                                         // initialize lcd

	lcd16x2_SetPosition(0,0);                               // set position
	lcd16x2_PrintString("Teste LCD 16x2");                  // write a string to lcd

	f = -9237.0989;
	lcd16x2_SetPosition(1,0);                               // set position
	lcd16x2_PrintFloat(f);                                  // convert and print float - internal function (limited)

	lcd16x2_SetPosition(0,15);                              // set position
	lcd16x2_Data('?');                                      // print character '?' on lcd

//	lcd16x2_ShitftLeft(1);                                  // shift left entire display
//	lcd16x2_ShitftRigh(1);                                  // shift right entire display

	while(1)
	{
	    lcd16x2_SetPosition(1, 11);                         // set position
	    lcd16x2_PrintInt((int_fast16_t)counter++);          // convet and print integer - internal function (limited)

	    _delay_cycles(10000);                             // delay
	}
}
