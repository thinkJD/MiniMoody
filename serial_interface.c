/*
 * serial_interface.c
 *
 */ 

/**********************************************************************************

Author:				Frank Andre
Copyright 2012 by:	Frank Andre
License:			This software is distributed under the creative commons license
					CC-BY-NC-SA.
Disclaimer:			This software is provided by the copyright holder "as is" and any 
					express or implied warranties, including, but not limited to, the 
					implied warranties of merchantability and fitness for a particular 
					purpose are disclaimed. In no event shall the copyright owner or 
					contributors be liable for any direct, indirect, incidental, 
					special, exemplary, or consequential damages (including, but not 
					limited to, procurement of substitute goods or services; loss of 
					use, data, or profits; or business interruption) however caused 
					and on any theory of liability, whether in contract, strict 
					liability, or tort (including negligence or otherwise) arising 
					in any way out of the use of this software, even if advised of 
					the possibility of such damage.
					
**********************************************************************************/


/********************************************************************************************

Simple serial Interface.

A one character command is followed by a decimal argument (0..255) and a final <return>.
r<arg><return> sets pwm channel 0 to value RGB2PWM(<arg>).
The channels 0..5 are identified by command characters r, g, b, R, G, B.
Command 'x' exits the serial control mode and continues the normal RGB sequence.

********************************************************************************************/

#include <inttypes.h>
#include <avr/io.h>
#include "serial_interface.h"


/*************
 * variables *
 *************/

uint8_t ser_command;
uint8_t ser_argument;

volatile uint8_t ser_state = SER_IDLE;


 
/*************
 * functions *
 *************/
 
/*======================================================================
    Function:    serInit
    Input:       none
    Output:      none
    Description: Setup serial interface.
    Tested:      no
  ======================================================================*/
void serInit(void)
{
	UCSRA = 0;
	UCSRB = (1<<RXCIE)|(1<<RXEN);		// enable RX interrupts
	UCSRC = (3<<UCSZ0);					// 8 data bits, no parity, 1 stop bit
	UBRRH = 0;
	UBRRL = BAUDRATE;
}


/*======================================================================
    Function:    serReceive
    Input:       none
    Output:      none
    Description: Receive byte. Used as interrupt service routine.
    Tested:      no
  ======================================================================*/
void serReceive(void)
{
	uint8_t ch, temp;
	 
	ch = UDR;		// read data register
	if (ch >= 'A') {
		ser_command  = ch;
		ser_argument = 0;
	}
	if (ch == 13) {
		if (ser_command == 'x') {
			ser_state = SER_IDLE;
		} else {
			ser_state = SER_SERVICE_REQUEST;
		}
	}
	if ((ch >= '0') && (ch <= '9')) {
		ser_argument <<= 1;			// ser_argument *= 10;
		temp = ser_argument;
		ser_argument <<= 2;
		ser_argument += temp;
		ser_argument += (ch - '0');
	}		
}

