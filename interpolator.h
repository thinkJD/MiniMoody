/*
 * interpolator.h
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


#ifndef INTERPOLATOR_H_
#define INTERPOLATOR_H_


#include "config.h"


/*************
 * constants *
 *************/

// number of interpolation channels
#ifndef CHANNEL_COUNT
	#define CHANNEL_COUNT	8
#endif

#ifndef STEPS
	#define STEPS	127		// number of interpolation steps
#endif


/**************
 * prototypes *
 **************/

void    interpolatorSetup(uint8_t from[], uint8_t to[]);
uint8_t interpolatorUpdate(uint8_t val[]);


#endif /* INTERPOLATOR_H_ */