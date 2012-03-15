/*
 * config.h
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


#ifndef CONFIG_H_
#define CONFIG_H_


/*************
 * constants *
 *************/

// processor clock frequency
#ifndef F_CPU
#define F_CPU		8000000
#endif

// push button inputs
#define PB_PORT		PORTD
#define PB_PIN		PIND
#define PB_DDR		DDRD
#define PB_PREV		(1<<PD4)	// button "previous sequence"
#define PB_NEXT		(1<<PD5)	// button "next sequence"
#define PB_SPEEDUP	(1<<PD6)	// button "speed-up"
#define PB_MASK		(PB_PREV | PB_NEXT | PB_SPEEDUP)
#define PB_ACK		0xFF
#define PB_DEBOUNCE	20		// debouncing time [ms]

// specify PWM output pins
#define PWM_PORT	PORTB
#define PWM_DDR		DDRB
#define PWM_CH0		PB0		// bit position of PWM channel 0
//#define PWM_INVERTED		// define if PWM outputs are active low

// number of PWM channels
#define CHANNEL_COUNT	6

#define PWM_MASK	( 0x3F << PWM_CH0 )	// bit mask for all PWM channels

// PWM resolution / maximum PWM value (range 1..127)
// this value represents maximum duty cycle
#define MAX_PWM			127

// maximum value for R, G and B
#define MAX_RGB			127
#define STEPS			MAX_RGB		// number of interpolation steps

// pwm frequency [Hz]
#define PWM_FREQ		150			// range 31..300 Hz (@ F_CPU=8MHz and MAX_PWM=127)

// brightness enhancement
// NOTE: This feature has been disabled!!!
// set both thresholds to 255 to turn brightness enhancement off
// #define BRT_THR1		64			// threshold 1
// #define BRT_THR2		96			// threshold 2
// #define BRT_ENH			1			// enhancement (0 = 100%, 1 = 50%, 2 = 25%, 3 = 12,5%)

// auto-save time [s]
#define AUTOSAVE_TIME	30			// after this time the current state is saved to EEPROM

// extended set of color sequences (un-comment to enable)
#define EXTENDED_SET

// eeprom addresses
#define EE_SEQ_INDEX	0			// index of current sequence
#define EE_SPEED		2			// current speed setting


/************
 * typedefs *
 ************/

typedef struct {
	uint8_t		time;					// transition time [in TRANS_TIME_UNITs]
	uint8_t		color[CHANNEL_COUNT];	// color channels
} rgbt_t;


typedef struct {
	rgbt_t*		seq;					// pointer to start of sequence data
	uint16_t	time_unit;				// time unit used for transition times
} sequence_descriptor_t;



#endif /* CONFIG_H_ */