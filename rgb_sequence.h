/*
 * rgb_sequence.h
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


#ifndef RGB_SEQUENCE_H_
#define RGB_SEQUENCE_H_


#include "config.h"


// time units for transition times
// If in the sequence definition the transition time is set to n, 
// it takes n * <time_unit> seconds to transition to the next color.
#define TIME_8SEC		(uint16_t)(8000.0 * (F_CPU / (8000.0 * STEPS)) + 0.5)
#define TIME_5SEC		(uint16_t)(5000.0 * (F_CPU / (8000.0 * STEPS)) + 0.5)
#define TIME_2SEC		(uint16_t)(2000.0 * (F_CPU / (8000.0 * STEPS)) + 0.5)
#define TIME_1SEC		(uint16_t)(1000.0 * (F_CPU / (8000.0 * STEPS)) + 0.5)
#define TIME_500MS		(uint16_t)( 500.0 * (F_CPU / (8000.0 * STEPS)) + 0.5)
#define TIME_200MS		(uint16_t)( 200.0 * (F_CPU / (8000.0 * STEPS)) + 0.5)
#define TIME_100MS		(uint16_t)( 100.0 * (F_CPU / (8000.0 * STEPS)) + 0.5)
#define TIME_50MS		(uint16_t)(  50.0 * (F_CPU / (8000.0 * STEPS)) + 0.5)
#define TIME_20MS		(uint16_t)(  20.0 * (F_CPU / (8000.0 * STEPS)) + 0.5)
#define TIME_10MS		(uint16_t)(  10.0 * (F_CPU / (8000.0 * STEPS)) + 0.5)
#define TIME_SLOWEST	TIME_1SEC
#define TIME_FASTEST	TIME_10MS


/*****************
 * RGB-sequences *
 *****************/

#include "rgb_sequence_standard.h"
//#include "rgb_sequence_twinbox.h"

#endif /* RGB_SEQUENCE_H_ */