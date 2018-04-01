/************************ Documentaion **************************/
/*
 * keypad.h
 *
 * Created: 01/04/2018 09:52:36 ص
 *  Author: Amr Mostafa
 */ 

/********************** Preprocessors ************************/
#include "keypad.h"

/***************** Functions efinitions **********************/	
			
// function to configure the keypad port for all the 8 pins of the keypad,
//		keypad 4 rows must be connected to port pints 0-3,
//		keypad 4 columns must be connected to port pints 4-7
// INUPUT: ...
// OUTPUT: ...
// NOTES: keypad 8 wires (4 rows + 4 columns) must all be connected to the same MCU port
void Keypad_Init(void)
{
	KEYPAD_DDR = 0x00;									// 4 rows pins 0-3 input , 4 columns pins 4-7 input
	KEYPAD_PORT |=1<<0 | 1<<1 | 1<<2 | 1<<3;			// pull-up rows , Tristate columns with high impedance
}

// function to scan the all 16 keys of the keypad,
//		and return the pressed key according to the selected keypad matrix
// INUPUT: keypad_select:
//				1>return pressed key from the keypad_1 matrix
//				2>return pressed key from the keypad_2 matrix
// OUTPUT: returnL: the pressed key (if any key is pressed) according to the selected keypad matrix
//					0xFF (if no key is pressed)
// NOTES: call this function inside while(1) or something like to continuously scanning the keypad
unsigned char Get_Keypad_PressedKey(unsigned char keypad_select)
{
	unsigned char row , colm;							// row,colm> keypad array current row and column
	for (colm = 0 ; colm <= 3 ; colm++)
	{
		_delay_ms(10);									// wait 10ms for button de-bouncing
		KEYPAD_DDR &=~(1<<4 | 1<<5 | 1<<6 | 1<<7);		// Tristate all columns with high impedance
		KEYPAD_DDR |=1 << (colm + 4);					// make only current column as output
		KEYPAD_PORT &=~(1 << (colm + 4) );				// make only current column output is low
		for (row = 0 ; row <= 3 ; row++)
		{
			// key considered pressed when pin reads 0
			if ( (KEYPAD_PIN & 1<<row) == 0)
			{
				// check whether to use standard keypad matrix OR calculator matrix
				if (keypad_select == 1)
				{
					return ( keypad_1[row][colm] );	// return the pressed key value from keypad_1 matrix
				}
				else if (keypad_select == 2)
				{
					return ( keypad_2[row][colm] );	// return the pressed key value from keypad_2 matrix
				}
			}
		}
	}
	return 0xff;		// return 0xff if no key press is detected
}