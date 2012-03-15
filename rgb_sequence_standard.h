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


/*****************
 * RGB-sequences *
 *****************/

// Color changes are stored as a sequence of RGBT tuples.
// An RGBT tuple contains a color and a time. 
// The color is encoded as a red, green, blue tuple (range 0..MAX_RGB).
// Time specifies how long it takes until the new color is achieved.
// Each sequence must have at least one RGBT entry plus the end marker.
// Note: Last RGBT tuple must have its time set to zero 
// to indicate the end of the sequence. {[r, g, b, R, G, B}, 0}

const rgbt_t red_glow[] PROGMEM = {
	{  20, {100,  30,   0, 110,  20,   0} },
	{  30, { 80,  60,   5, 127,   5,   0} },
	{  20, {120,  18,   3, 100,  85,   4} },
	{  30, {127,   0,   0, 120,   5,   0} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t vivid_green[] PROGMEM = {
	{   4, { 15, 125,  10,  50, 100,   0} },
	{   4, { 50, 100,   0,  30, 120,  10} },
	{   4, { 35,  90,   5,  20, 100,   0} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t aquatic[] PROGMEM = {
	{  15, {  0,  10, 127,   0,  20, 100} },
	{  10, {  5,  40,  70,   0,  10,  60} },
	{  10, {  0,   8, 120,   5, 120,  90} },
	{  12, {  0,  95,  25,   0,   0, 100} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t golden_sun[] PROGMEM = {
	{  10, { 80,  80,   5,  70,  90,   5} },
	{  10, { 90,  60,   0,  65,  80,  10} },
	{  10, {100, 100,  10,  80,  70,   5} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t green_poison[] PROGMEM = {
	{   4, {  0, 127,   0,   0, 127,   0} },
	{  20, { 30,  90,   0,   0, 100,  20} },
	{   4, {100,  50,   0, 100,  50,   0} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t dusk_till_dawn[] PROGMEM = {
	{   8, {100, 100,  15, 100, 100,  15} },
	{   8, { 80,  60,   5,  80,  60,   5} },
	{   4, { 50,  20,   3,  50,  20,   3} },
	{   4, { 10,  10,  15,  10,  10,  15} },
	{   8, {  2,   5,  40,   2,   5,  40} },
	{   8, {  6,  10,  30,   6,  10,  30} },
	{   2, { 10,  10,  15,  10,  10,  15} },
	{   6, { 50,  20,   3,  50,  20,   3} },
	{   4, { 80,  60,   5,  80,  60,   5} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t sky[] PROGMEM = {
	{  10, { 50,  80, 100,  60,  80,  90} },
	{  10, { 40,  60,  80,  50,  80, 100} },
	{  10, { 30,  60,  90,  40,  60,  80} },
	{  10, { 10,  40,  70,  30,  60,  90} },
	{  10, { 60,  80,  90,  10,  40,  70} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t pink_candy[] PROGMEM = {
	{  10, {120,  40,  90, 120,  40,  90} },
	{   5, {110,  30,  10, 100,  40,   5} },
	{  10, { 50,  20, 127,  50,  20, 127} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t heartbeat[] PROGMEM = {
	{  10, { 25,   0,   8,  23,   0,   5} },
	{  55, { 90,   0,   0,  90,   0,   0} },
	{   8, { 30,   0,   0,  30,   0,   0} },
	{   7, {120, 120,   0, 120, 120,   0} },
	{  10, { 30,   0,   0,  30,   0,   0} },
	{  10, {127,  20,   0, 127,  20,   0} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t red_green[] PROGMEM = {
	{   4, {127,   0,   0,   0, 127,   0} },
	{   4, {  0, 127,   0, 127,   0,   0} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t blue_yellow[] PROGMEM = {
	{   4, { 30,  40,   0,   0,   0, 127} },
	{   4, { 90, 120,   0,   0,   0,  50} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t color_wheel[] PROGMEM = {
	{   8, { 60,   0,   0,  60,   0,   0} },
	{   8, { 35,  55,   0,  35,  55,   0} },
	{   8, {  0,  90,   0,   0,  90,   0} },
	{   8, {  0,  65,  85,   0,  65,  85} },
	{   8, {  0,   0, 127,   0,   0, 127} },
	{   8, { 35,   0,  55,  35,   0,  55} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t warning[] PROGMEM = {
	{   4, {110, 127,   0,   0,   0,   0} },
	{   4, {  0,   0,   0, 110, 127,   0} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t lighthouse[] PROGMEM = {
	{   4, {  0,   6,   8,   0,   6,   8} },
	{   2, { 80, 120,  90,  80, 120,  90} },
	{   2, {  0,   6,   8,   0,   6,   8} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};

const rgbt_t flash_blue[] PROGMEM = {
	{ 200, {  0,  10,  40,   0,  10,  40} },
	{  80, {  0,  20,  60,   0,  25,  65} },
	{ 120, {  0,  15,  44,   0,  10,  40} },
	{  40, {  0,  20,  80,   0,  20,  80} },
	{  10, {  0,   5,  20,   0,   2,  23} },
	{   1, {127, 127, 127, 127, 127, 127} },
	{   1, {  0,   5,  20,   0,   2,  23} },
	{  40, {  0,  20,  60,   0,  10,  50} },
	{ 120, {  0,  15,  50,   0,   8,  34} },
	{   0, {  0,   0,   0,   0,   0,   0} }	// end of sequence marker
};


// list of all available sequences and their time base
const sequence_descriptor_t sequence_list[] PROGMEM = {
	{ red_glow, TIME_500MS },
	{ vivid_green, TIME_1SEC },
	{ aquatic, TIME_500MS },
	{ golden_sun, TIME_100MS },
	{ green_poison, TIME_1SEC },
	{ dusk_till_dawn, TIME_8SEC },
	{ sky, TIME_200MS },
	{ pink_candy, TIME_1SEC },
	{ heartbeat, TIME_100MS },
	{ red_green, TIME_5SEC },
	{ blue_yellow, TIME_5SEC },
	{ color_wheel, TIME_5SEC },
	{ warning, TIME_1SEC },
	{ lighthouse, TIME_1SEC },
	{ flash_blue, TIME_100MS },
};

#define SEQENCE_COUNT	(sizeof(sequence_list)/sizeof(sequence_list[0]))	// number of sequences in list

#define DEFAULT_SEQ		0		// index of default sequence which becomes active after power-up
								// if sequence index in EEPROM is out of range

