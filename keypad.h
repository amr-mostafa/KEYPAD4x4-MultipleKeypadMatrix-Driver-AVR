/**************************** Documentation ******************************/
/*
 * keypad.h
 *
 * Created: 01/04/2018 09:52:36 ص
 *  Author: Amr Mostafa
 */ 

/**************************** PreProcessors ******************************/
#ifndef KEYPAD_H_
#define KEYPAD_H_

#ifndef	F_CPU
#define F_CPU	16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define KEYPAD_DDR		DDRC						// KEYPAD port direction register
#define KEYPAD_PORT		PORTC						// KEYPAD port register
#define KEYPAD_PIN		PINC						// KEYPAD pin register

/******************* Prototypes and Global variables *********************/

// first keypad matrix
const static unsigned char keypad_1[4][4] = {
	{'1' , '2' , '3' , 'A' },
	{'4' , '5' , '6' , 'B' },
	{'7' , '8' , '9' , 'C' },
	{'*' , '0' , '#' , 'D' } };

// second keypad matrix
const static unsigned char keypad_2[4][4] = {
		{'7' , '8' , '9' , '+' },
		{'4' , '5' , '6' , '*' },
		{'1' , '2' , '3' , '-' },
		{'0' , '.' , '=' , '/' } };
			
// function to configure the keypad port for all the 8 pins of the keypad,
//		keypad 4 rows must be connected to port pints 0-3,
//		keypad 4 columns must be connected to port pints 4-7
// INUPUT: ...
// OUTPUT: ...
// NOTES: keypad 8 wires (4 rows + 4 columns) must all be connected to the same MCU port
void Keypad_Init(void);

// function to scan the all 16 keys of the keypad,
//		and return the pressed key according to the selected keypad matrix
// INUPUT: keypad_select:
//				1>return pressed key from the keypad_1 matrix
//				2>return pressed key from the keypad_2 matrix
// OUTPUT: returnL: the pressed key (if any key is pressed) according to the selected keypad matrix
//					0xFF (if no key is pressed)
// NOTES: call this function inside while(1) or something like to continuously scanning the keypad
unsigned char Get_Keypad_PressedKey(unsigned char keypad_select);

#endif /* KEYPAD_H_ */