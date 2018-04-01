/**************************** Documentation ******************************/
/*
 * inlinedebounce.h
 *
 * Created: 18/02/2018 07:47:40 م
 *  Author: Amr Mostafa
 */ 

#ifndef INLINEDEBOUNCE_H_
#define INLINEDEBOUNCE_H_
#include "debounce.h"

/************************ Functions Definitions **************************/

// debouncing implementation function using read of 4 samples of buttons input
// and confirm a press when all 4 samples are equal .. read 1 sample each 10ms(or less, but this works perfect)
// used to: - remove buttons bounce
//			- save up to 8 buttons press to enable main recognize any press while it's busy
//			- get rid of any interference signals coming from around devices
// INPUT: ...
// OUTPUT: ...
// NOTES: - inline keyword: to get ride of the stack call overhead for the interrupt usage
//		  - static keyword: to make the static variables defined in the source file include this .h file
//			are specific to it as if another source file included this .h file, it will create its own
//			static variables too .. and to allow main OR other source files to create their own static
//			variables wiht the same names maybe without conflict with those created by this function.
//		  - defined in .h file: as compiler needs to see inline functions definitions in the same file
//			in order to inline them, so the compiler now can see the definition of that inline function
//			and able to replace calls by the actual implementation of this function.
//		  - if you put the function in the header, all the .c files where it can be inlined can
//			see the "source" of your function and the inlining can be done easlyby the compiler
//			Otherwise the inlining would have to be done by the linker where it would be much more difficult to do.
//		  - this function must be called from aTimer ISR each 10ms to continuously read and update the 8 buttons states
//		  - CPU is faster than button mechanical bounce, so with no delay of some milli seconds, the CPU will read the
//			real-pressed edge 4 times so fast and consider it as real press(we need a confirmed period of pressed
//			not the pressed edge), so for 1 real press, CPU will consider many pressed + not pressed states.
inline static void Button_Press_Debounce(void)
{
	unsigned char current_state = 0;			// to hold 8 buttons immediate read state as 1>pressed OR 0>not pressed
	unsigned char buttons_changed = 0;			// to hold which buttons has changed 1>changed OR 0>not changed
	static unsigned char buttons_state = 0;		// keep track of current debounced button confirmed press as 1>pressed OR 0>not pressed
	// use 2 byte variable as 8 decremental counters .. each counter is 2 bits
	// counts from 3 as 2,1,0 then overflow and be 3 which is 11 binary..awesome ^-^
	// before	decimal		after
	// H	L				H	L
	// 0	0	0	>>		1	1	>>	1
	// 0	1	1	>>		0	0	>>	0
	// 1	0	2	>>		0	1	>>	1
	// 1	1	3	>>		1	0	>>	2
	// So we use ~(count_hight ^ count_low) to decrease the high bits counter
	// then use ~(count_low) to decrease the low bits counter
	static unsigned char count_hight = 0;		// this is the high bits portion of the 8 counters
	static unsigned char count_low = 0;			// this is the low bits portion of the 8 counters
	
	// check if any button is pressed>1 OR not pressed>0 for that tiny moment
	// ~ to convert the -logic due to internal pullup resistors to +logic
	current_state = ~KEY_PIN;
	// we don't want to decrease all 8 buttons counters at once, only those corresponding to
	// buttons have changed and other counters for unchanged buttons must be reset: binary 11
	// first, we must know which button is changed by this XOR operation
	buttons_changed = current_state ^ buttons_state;		// detect a change>1 OR not changed>0
	// then we decrement for changed buttons and reset for unchanged buttons .. we do this by
	// masking with & before the moment we gonna ~, EX: (0000 0001 & count_low) reads bit0 (the low bit of
	// changed button counter) as it, and clears others to be 0
	// so they be 1111 111x when use ~
	count_hight = ~( buttons_changed & (count_hight ^ count_low) );	// decrease the high bits portion of the 8 counters by 1 OR reset
	count_low = ~(buttons_changed & count_low);						// decrease the low bits portion of the 8 counters by 1 OR reset
	buttons_changed &=count_hight & count_low;						// update buttons_changed bits to have only 1s for the bits those overflows
	
	buttons_state ^=buttons_changed;		// update for buttons changed from 0>1 OR 1>0 .. keep other states as they are(friendly toggling ^_^)
	buttons_down |=	buttons_changed & buttons_state;	// update the global variable with only pressed buttons 0>1 and keep unread pressed by main
}


#endif /* INLINEDEBOUNCE_H_ */