/**************************** Documentation ******************************/
/*
 * timers.c
 *
 * Created: 17/02/2018 06:10:46 ص
 *  Author: Amr Mostafa
 */ 
/**************************** Preprocessors ******************************/
#include <avr/io.h>
#include "timers.h"
/**************************** Functions definition ******************************/

// function to initialize Timer0 in normal mode by polling its overflow flag(no interrupt)
// INPUT: ...
// OUTPUT: ...
// NOTES: call to this function will not make Timer0 start counting, just configures its mode and firing mechanism
void Timer0_NM_Polling_Init(void)
{
	// timer0 initialize
	TCCR0 &=~(1<<CS00 | 1<<CS01 | 1<<CS02);			// stop timer0 while initializing
	TCCR0 &= ~(1<<WGM00 | 1<<WGM01);				// normal mode
	TIMSK &= ~(1<<TOIE0);							// disable overflow interrupt
}

// function to be invoked when needed to perform very precise busy-wait loop delay in milli seconds
// uses Timer0 in normal mode by polling its overflow flag(no interrupt)
// INPUT: number of milli seconds
// OUTPUT: ...
// NOTES: - you must define/edit the F_CPU for the current CPU clock in the timers.h file
//		  - you must define/edit the prescaler CSxx bits mask and the prescaler value in the timers.h file
//		  - you must define/edit the timer required delay in milli seconds unit in the timers.h file
void Timer0_NM_Polling_Delay_ms(unsigned int milliSec)
{
	while (milliSec--)													// wait in this loop till there is no more milli seconds
	{
		TCNT0 = (256 - TIMER0_MILLISEC_DELAY / TIMER0_TIME_PERIOD);		// load Timer0 with macros pre-defined n.of ticks required till overflow
		TCCR0 |=TIMER0_CS02_01_00_PRESCALER_BITS_MASk;					// start counting with macros pre-defined prescaler
		while( !(TIFR & 1<<TOV0) );										// wait till overflow
		TCCR0 &=~(1<<CS00 | 1<<CS01 |1<<CS02);							// stop timer after macros pre-defined delay is finished
		TIFR |=1<<TOV0;													// clear flag by set
	}
}

// function to initialize Timer0 in CTC mode with timer interrupt
// compare match occurrence will fire its ISR each n.of ticks calculated using the pre-defined macros in timers.h file
// INPUT: ...
// OUTPUT: ...
// NOTES: - you must define/edit the F_CPU for the current CPU clock in the timers.h file
//		  - you must define/edit the prescaler CSxx bits mask and the prescaler value in the timers.h file
//		  - you must define/edit the timer required delay in milli seconds unit in the timers.h file
//		  - you must call sei() in your main to activate the glabal interrupt flag
//		  - you must call the Timer0 CTC ISR in your main file with the required interrupt task
void Timer0_CTC_Interrupt_DELAY_Init(void)
{
	TCCR0 &=~(1<<CS00 | 1<<CS01 | 1<<CS02);							// stop timer while initializing
	TCCR0 |= 1<<WGM01;												// CTC mode
	TIMSK |=1<<OCIE0;												// enable interrupt for compare match
	TCCR0 |=TIMER0_CS02_01_00_PRESCALER_BITS_MASk;					// start counting macros pre-defined n.of ticks
	OCR0 = TIMER0_MILLISEC_DELAY / TIMER0_TIME_PERIOD - 1;			// compare match interrupt occurs after macros pre-defined n.of ticks
}