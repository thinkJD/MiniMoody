/*
 * interpolator.c
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

Linear interpolation between 7-bit values in n steps.
Note: n >= abs(end value - start value)

********************************************************************************************/

#include <inttypes.h>
#include <avr/pgmspace.h>
#include "interpolator.h"


/*************
 * variables *
 *************/

static int8_t  delta[CHANNEL_COUNT];
static int8_t  accu[CHANNEL_COUNT];
static uint8_t q;
static uint8_t incr[CHANNEL_COUNT];		// 1 = increment, 0 = decrement


 
/*************
 * functions *
 *************/
 
/*======================================================================
    Function:    interpolatorSetup
    Input:       array of start values, array of end values
    Output:      transition time
    Description: Setup the interpolator.
    Tested:      no
  ======================================================================*/
void interpolatorSetup(uint8_t from[], uint8_t to[])
{
	uint8_t i;
	int8_t  f, t;

	for(i = 0; i < CHANNEL_COUNT; i++) {
		f = (int8_t) from[i];
		if (f < 0) { f = 127;}
		t = (int8_t) to[i];
		if (t < 0) { t = 127;}

		if (t > f) {
			delta[i] = t - f;
			incr[i]  = 1;
		} else {
			delta[i] = f - t;
			incr[i]  = 0;			
		}
		accu[i] = -(STEPS/2);
	}
	q = STEPS;
}


/*======================================================================
    Function:    interpolatorUpdate
    Input:       array of values to be updated
    Output:      number of remaining steps for the transition to complete
    Description: Calculate one interpolation step by changing the values 
	             towards the desired target values.
	             Call this function periodically.
    Tested:      no
  ======================================================================*/
uint8_t interpolatorUpdate(uint8_t val[])
{
	uint8_t i;
	
	for(i = 0; i < CHANNEL_COUNT; i++) {
		accu[i] += delta[i];
		if (accu[i] > 0) {
 			if (incr[i]) { val[i]++; }
 				else     { val[i]--; }
			accu[i] -= STEPS;
		}
	}
	q--;
	return(q);
}



