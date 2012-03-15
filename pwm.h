/*
 * pwm.h
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


#ifndef PWM_H_
#define PWM_H_


#include "config.h"


/*************
 * constants *
 *************/

// number of PWM channels
#ifndef CHANNEL_COUNT
	#define CHANNEL_COUNT	8
#endif

// maximum PWM value (range 1..255)
// this value represents maximum duty cycle
#ifndef MAX_PWM
	#define MAX_PWM			255
#endif


/**************
 * prototypes *
 **************/

//void    pwmReset(uint8_t p[]);
uint8_t pwmUpdate(uint8_t p[]);


#endif /* PWM_H_ */