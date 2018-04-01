/************************* Documentation ****************************/
/*
 * KEYPAD_4x4.c
 *
 * Created: 01/04/2018 09:52:36 ص
 * Author : Amr Mostafa
 */ 

/**************************** PreProcessors ***************************/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "debounce.h"
#include "keypad.h"
	
/******************************* Functions *****************************/
int main(void)
{
	unsigned char keypad_select;					// variable to hold the selected keypad matrix
	unsigned char key;								// variable to hold the pressed key from keypad
	LCD_Init();										// initialize the LCD
	Debounce_Init();								// initialize the push buttons driver
	Keypad_Init();									// initialize the keypad
	
	keypad_select = 1;								// select keypad matrix 1 initially
	LCD_Line_Column(2 , 1);							// go to line 2 and position 1 in LCD
	LCD_WriteString("current keypad:");				// send this string to LCD
	LCD_Line_Column(2 , 16);						// go to line 2 and position 16 in LCD
	LCD_WriteData(' ');								// clear the 16th position in LCD
	LCD_Line_Column(2 , 16);						// go to line 2 and position 16 in LCD
	LCD_WriteData('1');								// show that keypad matrix 1 is currently used
	while (1) 
    {
		if (Get_Keys_Pressed(1<<KEY6))
		{
			LCD_Clear();							// clear LCD once detecting a change in keypad matrix selection
			LCD_Line_Column(2 , 1);					// go to line 2 and position 1 in LCD
			LCD_WriteString("current keypad:");		// send this string to LCD
			LCD_Line_Column(2 , 16);				// go to line 2 and position 16 in LCD
			LCD_WriteData(' ');						// clear the 16th position in LCD
			LCD_Line_Column(2 , 16);				// go to line 2 and position 16 in LCD
			
			// check which keypad matrix to be selected
			if (keypad_select == 1)
			{
				keypad_select = 2;					// select keypad matrix 2 if the previous was keypad matrix 1
				LCD_WriteData('2');					// show that keypad matrix 2 is currently used
			}
			else if (keypad_select == 2)
			{
				keypad_select = 1;					// select keypad matrix 1 if the previous was keypad matrix 2
				LCD_WriteData('1');					// show that keypad matrix 1 is currently used
			}
		}
		
		// scan the keypad and save the pressed key
		key = Get_Keypad_PressedKey(keypad_select);
		
		// if any key is pressed, then print to LCD .. otherwise do nothing
		if ( key != 0xff )
		{
			LCD_Line_Column(1 , 1);					// go to line 1 and position 1 in LCD
			LCD_WriteData(' ');						// clear the 1th position in LCD
			LCD_Line_Column(1 , 1);					// go to line 1 and position 1 in LCD
			LCD_WriteData(key);						// print the pressed key value on LCD
		}
		_delay_ms(100);
    }
	
}

