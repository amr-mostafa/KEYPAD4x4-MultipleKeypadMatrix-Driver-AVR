/************************** Documentation ****************************/
/*
 * debounce.c
 *
 * Created: 17/02/2018 02:02:21 ص
 *  Author: Amr Mostafa
 */

/**************************** PreProcessors ******************************/
#include <avr/io.h>
#include "avr/interrupt.h"
#include "debounce.h"
#include "inlinedebounce.h"
#include <util/atomic.h>
#include <avr/interrupt.h>
#include "timers.h"

/******************* Prototypes and Global variables *********************/
volatile unsigned char buttons_down = 0;		// define sharable pressed buttons variable
/************************ Functions Definitions **************************/

// function to initialize port where the 8 buttons are connected to
// INPUT: ...
// OUTPUT: ...
// NOTES: call this function only when need buttons in software as it changes the whole port function
void Debounce_Init(void)
{
	KEY_DDR = 0x00;			// buttons port is input
	KEY_PORT = 0xff;		// internal pullup resistors enable on buttons port
	sei();					// enable interrupt
	Timer0_CTC_Interrupt_DELAY_Init();			// enable timer0 ctc mode with delay functionality
}

// function to get the pressed buttons saved in the sharable global variable buttons_down
// INPUT: button mask .. EX: 1<<KEY0 reads button connected to pin0 of the buttons port
// OUTPUT: return 8 bits variable holds 1>pressed button OR 0>not pressed buttons
// NOTES: the function clears those INPUT buttons bits from the sharable global
//		  variable buttons_down  after software OR main reads(call this function)them.
unsigned char Get_Keys_Pressed(unsigned char pins_mask)
{
	 // Creates a block of code that is guaranteed to be executed atomically so no ISR interrupt main while reading button
	 // ATOMIC_RESTORESTATE input parameter saves the global interrupt flag, disable it then return its saved state again after function end
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		// note: pins_mask is reused again for effective memory use
		pins_mask &=buttons_down;			// read button(s)
		buttons_down ^=pins_mask;			// toggle pressed buttons: means clear them after main read them
	}
	return pins_mask;
}

// the Timer0 CTC ISR that calls the inline debounce function each 10ms
ISR(TIMER0_COMP_vect)
{
	Button_Press_Debounce();
}

