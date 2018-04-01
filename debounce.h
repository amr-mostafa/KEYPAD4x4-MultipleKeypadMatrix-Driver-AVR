/**************************** Documentation ******************************/
/*
 * debounce.h
 *
 * Created: 17/02/2018 02:02:51 ص
 *  Author: Amr Mostafa
 */ 

/**************************** Preprocessors ******************************/
#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_
#include <avr/io.h>
#define KEY_DDR			DDRD		// 8 buttons port DRR register
#define KEY_PORT		PORTD		// 8 buttons port PORT register
#define KEY_PIN			PIND		// 8 buttons port PIN register
#define KEY0		0
#define KEY1		1
#define KEY2		2
#define KEY3		3
#define KEY4		4
#define KEY5		5
#define KEY6		6
#define KEY7		7

/******************* Prototypes and Global variables *********************/

// declare sharable pressed buttons variable to be referenced from all source files need it
// definition for it lives in the debounce.c file
extern volatile unsigned char buttons_down;

// function to initialize port where the 8 buttons are connected to
// INPUT: ...
// OUTPUT: ...
// NOTES: call this function only when need buttons in software as it changes the whole port function
void Debounce_Init(void);

// function to get the pressed buttons saved in the sharable global variable buttons_down
// INPUT: button mask .. EX: 1<<KEY0 reads button connected to pin0 of the buttons port
// OUTPUT: return 8 bits variable holds 1>pressed button OR 0>not pressed buttons
// NOTES: the function clears those INPUT buttons bits from the sharable global
//		  variable buttons_down  after software OR main reads(call this function)them.
unsigned char Get_Keys_Pressed(unsigned char pins_mask);
#endif /* DEBOUNCE_H_ */