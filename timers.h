/**************************** Documentation ******************************/
/*
 * timers.h
 *
 * Created: 17/02/2018 06:10:31 ص
 *  Author: Amr Mostafa
 */

/**************************** Preprocessors ******************************/
#ifndef TIMERS_H_
#define TIMERS_H_
#include <avr/io.h>

#ifndef F_CPU					// if CPU clock not defined
#define F_CPU	16000000UL		// then define it as 16MHZ
#endif

#define TIMER0_CS02_01_00_PRESCALER_BITS_MASk		(1<<CS02 | 1<<CS00)				// CSxx bits mask
#define TIMER0_PRESCALER							(1024)							// prescaler value
#define TIMER0_CLOCK								(F_CPU/TIMER0_PRESCALER)		// Timer0 clock is: 16000 000 / 1024 = 15625
#define TIMER0_TIME_PERIOD							(1.0/TIMER0_CLOCK)				// Timer0 tick period is: 1 / 15625 = 6.4*10e-5 = 0.000 064 sec (64 uSec)
#define TIMER0_MILLISEC_DELAY						(0.010)							// I need Timer0 to wait for 10 milli seconds

/******************* Prototypes and Global variables *********************/

// function to initialize Timer0 in normal mode by polling its overflow flag(no interrupt)
// INPUT: ...
// OUTPUT: ...
// NOTES: call to this function will not make Timer0 start counting, just configures its mode and firing mechanism
void Timer0_NM_Polling_Init(void);

// function to be invoked when needed to perform very precise busy-wait loop delay in milli seconds
// uses Timer0 in normal mode by polling its overflow flag(no interrupt)
// INPUT: number of milli seconds
// OUTPUT: ...
// NOTES: - you must define/edit the F_CPU for the current CPU clock in this file
//		  - you must define/edit the prescaler CSxx bits mask and the prescaler value in the timers.h file
//		  - you must define/edit the timer required delay in milli seconds unit in the timers.h file
void Timer0_NM_Polling_Delay_ms(unsigned int milliSec);

// function to initialize Timer0 in CTC mode with timer interrupt
// compare match occurrence will fire its ISR each n.of ticks calculated using the pre-defined macros in timers.h file
// INPUT: ...
// OUTPUT: ...
// NOTES: - you must define/edit the F_CPU for the current CPU clock in this file
//		  - you must define/edit the prescaler CSxx bits mask and the prescaler value in the timers.h file
//		  - you must define/edit the timer required delay in milli seconds unit in the timers.h file
//		  - you must call sei() in your main to activate the glabal interrupt flag
//		  - you must call the Timer0 CTC ISR in your main file with the required interrupt task
void Timer0_CTC_Interrupt_DELAY_Init(void);

#endif /* TIMERS_H_ */