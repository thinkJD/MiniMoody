/*
 * pwm.c
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

Implementation of a simple multi channel 8-bit software PWM.

********************************************************************************************/

#include <inttypes.h>
#include "pwm.h"


/*************
 * variables *
 *************/

static uint8_t  counter;

 
/*************
 * functions *
 *************/
 
/*======================================================================
    Function:    pwmReset
    Input:       array of pwm values
    Output:      none
    Description: Reset PWM counter.
    Tested:      no
  ======================================================================*/
/*
void pwmReset(uint8_t p[])
{
	uint8_t i;
	
	for(i = 0; i < CHANNEL_COUNT; i++) {
		p[i] = 0;
	}
	counter = 0;
}
*/


/*======================================================================
    Function:    pwmUpdate
    Input:       array of pwm values
	                   0 =   0 % duty cycle (output off)
				 MAX_PWM = 100 % duty cycle (output on)
    Output:      bit pattern where each bit indicates if the corresponding PWM channel 
	             output is active (= 1) or inactive (= 0)
    Description: Advances the PWM generator one step.
	             Call this function periodically.
    Tested:      no
  ======================================================================*/
uint8_t pwmUpdate(uint8_t p[])
{
	uint8_t i, output;

	if (counter) { counter--; }
	else     { counter = MAX_PWM - 1; }

	output = 0;
	i = CHANNEL_COUNT;
	while (i > 0) {
		i--;
		output <<= 1;				// shift output
		if (counter < p[i]) {		// channel active?
			output |= 1;			// set lsb
		}
	}
	return(output);
}



