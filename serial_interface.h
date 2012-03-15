/*
 * serial_interface.h
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


#ifndef SERIAL_INTERFACE_H_
#define SERIAL_INTERFACE_H_


#include "config.h"


/*************
 * constants *
 *************/

// baud rates
#define BAUD_2400	(uint8_t)(F_CPU / (16.0 * 2400) - 1 + 0.5)
#define BAUD_4800	(uint8_t)(F_CPU / (16.0 * 4800) - 1 + 0.5)
#define BAUD_9600	(uint8_t)(F_CPU / (16.0 * 9600) - 1 + 0.5)
#define BAUD_19200	(uint8_t)(F_CPU / (16.0 * 19200) - 1 + 0.5)

#define BAUDRATE	BAUD_2400

// serial interface states
#define SER_IDLE				0
#define SER_SERVICE_REQUEST		1	// command termination character (CHR(13)) has been received
#define SER_WAITING				2	// waiting on next command

extern volatile uint8_t ser_state;
extern uint8_t ser_command;
extern uint8_t ser_argument;


/**************
 * prototypes *
 **************/

void    serInit(void);
void    serReceive(void);


#endif /* SERIAL_INTERFACE_H_ */