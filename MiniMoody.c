/*
 * MiniMoody.c
 *
 */ 

/**********************************************************************************

MiniMoody - Implementation of a tiny RGB color changing desktop light.


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


#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "config.h"
#include "rgb_sequence.h"
#include "pwm.h"
#include "interpolator.h"
#include "serial_interface.h"


#ifndef NULL
	#define NULL	0
#endif


/********************
 * global variables *
 ********************/

uint8_t pwm[CHANNEL_COUNT];			// duty cycles of PWM channels (0 = 0%, MAX_PWM = 100%)
uint8_t pwm_target[CHANNEL_COUNT];	// transition end values
uint16_t ocr1a_reload;
volatile uint16_t autosave_timer;
volatile uint8_t button = 0;		// push button event
									// one bit per button (1 = pressed, 0 = released)
volatile uint8_t trans_timer;		// transition timer
uint8_t trans_time;					// current transition time


/******************************
 * interrupt service routines *
 ******************************/

ISR(TIMER0_COMPA_vect)
{
	// triggers for every PWM step
	
	uint8_t output;
	
	output = pwmUpdate(pwm) << PWM_CH0;
	#ifdef PWM_INVERTED
		output ^= PWM_MASK;
	#endif
	
	output  |= PWM_PORT & ~PWM_MASK;
	PWM_PORT = output;
}


ISR(TIMER1_COMPA_vect)
{
	// color transitions
	uint16_t t;
	
	OCR1A += ocr1a_reload;		// setup next cycle
	t = trans_timer;
	if (t) {
		t--;
		trans_timer = t;
	}
}


ISR(TIMER1_COMPB_vect)
{
	// push button sampling
	
	static uint8_t old_button_state = 0;
	uint8_t new_button_state = 0;
	uint16_t autosave;
	
	OCR1B += (uint16_t)(PB_DEBOUNCE * (F_CPU / 8000.0) + 0.5);		// setup next cycle
	new_button_state = ~PB_PIN & PB_MASK;

	if (new_button_state) {
//		autosave_timer = (uint16_t)(AUTOSAVE_TIME * 1000.0 / PB_DEBOUNCE);
		autosave = (uint16_t)(AUTOSAVE_TIME * 1000.0 / PB_DEBOUNCE);
	} else {
		autosave = autosave_timer;
	}
//	if (autosave_timer > 1) { autosave_timer--; }
	if (autosave > 1) { autosave--; }
	autosave_timer = autosave;
	
	if (old_button_state == 0) {
		button = new_button_state;
	}
	old_button_state = new_button_state;
}


ISR(USART_RX_vect)
{
	serReceive();
}

	
/*************
 * functions *
 *************/

/*======================================================================
    Function:    InitHardware
    Input:       none
    Output:      none
    Description: Set input / output ports. Setup timer.
    Tested:      no
  ======================================================================*/
void InitHardware(void)
{
	PB_DDR  &= ~(PB_MASK);							// switch button pins to input
	PB_PORT |=   PB_MASK;							// enable pull-ups

	PWM_DDR  |=  PWM_MASK;							// switch pwm channels to output
	PWM_PORT &= ~PWM_MASK;

	// timer 0
	// OC0A generates interrupts for each pwm step
	TCCR0A = (2<<WGM00);							// CTC mode
	TCCR0B = (0<<WGM02)|(2<<CS10);					// CTC mode, prescaler = 1:8
	OCR0A  = (uint8_t)(F_CPU / (8.0 * PWM_FREQ  * MAX_PWM) + 0.5) - 1;
	
	// timer 1
	// OC1A generates interrupts for interpolator
	// OC1B generates interrupts for sampling of push buttons
	TCCR1A = (0<<WGM10);							// normal (freerunning) mode
	TCCR1B = (0<<WGM12)|(2<<CS10);					// normal mode, prescaler = 1:8
	OCR1A  = TIME_1SEC;
	OCR1B  = (uint16_t)(PB_DEBOUNCE * (F_CPU / 8000.0) + 0.5);

	TIMSK = (1<<OCIE0A)|(1<<OCIE1A)|(1<<OCIE1B);
}


/*======================================================================
    Function:    LoadRGB
    Input:       pointer to (R,G,B) tuple in RAM (target)
	             pointer to (R,G,B,time) tuple in flash memory
    Output:      none
    Description: Load RGB values from flash memory into RAM.
    Tested:      no
  ======================================================================*/
void LoadRGB(uint8_t rgb[], rgbt_t* rgbt_ptr)
{
	uint8_t i;
	
	for(i = 0; i < CHANNEL_COUNT; i++) {
		rgb[i] = pgm_read_byte( &((rgbt_ptr->color)[i]) );
	}
}


/*======================================================================
    Function:    GetTransTime
    Input:       pointer to (R,G,B,time) tuple in flash memory
    Output:      transition time
    Description: Return transition time of (R,G,B,time) tuple in flash memory.
    Tested:      no
  ======================================================================*/
inline uint8_t GetTransTime(rgbt_t* rgbt_ptr)
{
	return( pgm_read_byte(&(rgbt_ptr->time)) );
}


/*======================================================================
    Function:    RGB2PWM
    Input:       led brightness value
    Output:      pwm duty cycle value
    Description: This function implements a non-linear mapping from RGB values 
	             to PWM values to compensate for the non-linear brightness-current 
				 curve of leds. 
	             by 
    Tested:      no
  ======================================================================*/
/*
uint8_t RGB2PWM(uint8_t b)
{
	if (b >= BRT_THR1) {
		b += ((b - BRT_THR1) >> BRT_ENH);
	} 
	if (b >= BRT_THR2) {
		b += ((b - BRT_THR2) >> BRT_ENH);
	}
	return(b);
}
*/

/*======================================================================
    Function:    SetupTransition
    Input:       pointer to start of RGB sequence
	             pointer to (R,G,B) target tuple
    Output:      pointer to next (R,G,B) target tuple
    Description: Set up transition from current color to target color.
	             If target == NULL the (R,G,B) tuple of the sequence start is loaded.
    Tested:      no
  ======================================================================*/
rgbt_t* SetupTransition(rgbt_t* seq, rgbt_t* target)
{
	uint8_t t;
	
	if (target == NULL) {
		LoadRGB(pwm, seq);						// load sequence start values
		target = seq;		
	}
	else {
		LoadRGB(pwm_target, target);			// load transition target
		interpolatorSetup(pwm, pwm_target);
		t = GetTransTime(target);
		trans_time  = t;
		trans_timer = t;						// start transition timer
	}

	target++;								// next tuple
	t = GetTransTime(target);
	if (t == 0) {							// end of sequence?
		target = seq;						// -> then start from begin of sequence
	}
	return(target);
}


/*======================================================================
    Function:    SetupSequence
    Input:       index of desired sequence
    Output:      pointer to start of sequence
    Description: 
    Tested:      no
  ======================================================================*/
rgbt_t* SetupSequence(uint8_t index)
{
	ocr1a_reload = pgm_read_word( &(sequence_list[index].time_unit) );
	return( (rgbt_t*) pgm_read_word( &(sequence_list[index].seq) ) );
}


/********
 * main *
 ********/

int main(void)
{
	uint8_t seq_index;		// index of currently active RGB sequence
	rgbt_t* sequence;		// pointer to current rgb sequence
	rgbt_t* rgbt;			// pointer to the current target (R,G,B,time) tuple
	uint8_t temp;
		
	InitHardware();
	serInit();
//	pwmReset(pwm);

	seq_index = (uint8_t) eeprom_read_word((uint16_t*)EE_SEQ_INDEX);
	if (seq_index >= SEQENCE_COUNT) {
		seq_index = DEFAULT_SEQ;
		sequence = SetupSequence(seq_index);
	}
	else {
		sequence = SetupSequence(seq_index);
		ocr1a_reload = eeprom_read_word((uint16_t*)EE_SPEED);
	}
		
	rgbt = SetupTransition(sequence, NULL);
	rgbt = SetupTransition(sequence, rgbt);

	sei();									// enable interrupts
	
    while(1)
    {
		switch (button) {
			case PB_SPEEDUP:				// --- double speed ---
				button = PB_ACK;			// acknowledge button event
				if (ocr1a_reload >= (TIME_FASTEST << 1)) {
					ocr1a_reload >>= 1;
				} else {
					sequence = SetupSequence(seq_index);
					rgbt     = SetupTransition(sequence, NULL);
					rgbt     = SetupTransition(sequence, rgbt);
				}					
				break;
			case PB_PREV:					// --- previous sequence ---
				button = PB_ACK;			// acknowledge button event
				if (seq_index > 0) {
					seq_index--;
				} else {
					seq_index = SEQENCE_COUNT - 1;
				}
				sequence = SetupSequence(seq_index);
				rgbt     = SetupTransition(sequence, NULL);
				rgbt     = SetupTransition(sequence, rgbt);
				break;
			case PB_NEXT:					// --- next sequence ---
				button = PB_ACK;			// acknowledge button event
				if (seq_index < (SEQENCE_COUNT-1)) {
					seq_index++;
				} else {
					seq_index = 0;
				}
				sequence = SetupSequence(seq_index);
				rgbt     = SetupTransition(sequence, NULL);
				rgbt     = SetupTransition(sequence, rgbt);
				break;
		}
		
		if (ser_state == SER_IDLE) {
			if (trans_timer == 0) {				// if timer has elapsed it's time for a new interpolation step
				trans_timer = trans_time;			// restart transition timer
				if (interpolatorUpdate(pwm) == 0) {	// transition finished?
					rgbt = SetupTransition(sequence, rgbt);	// yes -> setup new transition
				}
			}
		}		

		if (ser_state == SER_SERVICE_REQUEST) {
			temp = 0;
			switch (ser_command) {
//				case 'r': temp = 0; break;
				case 'g': temp = 1; break;
				case 'b': temp = 2; break;
				case 'R': temp = 3; break;
				case 'G': temp = 4; break;
				case 'B': temp = 5; break;
			}
 			pwm[temp] = ser_argument;
			ser_state = SER_WAITING;
		}
		
		if (autosave_timer == 1) {
			eeprom_write_word((uint16_t*)EE_SEQ_INDEX, (uint16_t)seq_index);
			eeprom_write_word((uint16_t*)EE_SPEED, ocr1a_reload);
			autosave_timer = 0;
		}

    } // of while(1)
}


