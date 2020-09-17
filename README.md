# KEYPAD 4x4: Multiple Keypad Matrix Driver for AVR Microcontroller.
4x4 Keyypad driver for the Atmega32/16 microcontroller with the ability to change the keypad labels from **numbers and alphabetic** keypad to **calculator** keypad, which I call **Multiple keypad**.

![image](https://i.ibb.co/P5SJZnw/IMG-20180401-163445.jpg)

# Target microcontrollers:
- This library uses only I/O ports & registers, so it can be used for all 8-bits AVRs family microcontrollers and some other simple 8-bits microcontrollers by editing the I/O ports & registers definitions macros in [keypad.h](https://github.com/amr-mostafa/KEYPAD4x4-MultipleKeypadMatrix-Driver-AVR/blob/master/keypad.h) file.

# Features:
- Assuring buttons debouncing for better user experience and system responding.
- Allow the user to select between 2 keypad matrix at the run time; **numbers and alphabetic** keypad and **calculator** keypad.

# Functions Supported:
* Initializing function:
```
void Keypad_Init(void);
```
* Operating function that scans all 16 keys of the keypad.
* This function takes the keypad matrix as an input and returns the pressed key according to the selected keypad matrix:
```
unsigned char Get_Keypad_PressedKey(unsigned char keypad_select);
```

# Requirements:
- compiled for AVR/GNU C Compiler (avr-gcc) for 8 bits AVR micro-controllers

# How to use:
- All Keypad configurations related to I/O interfacing are placed in [keypad.h](https://github.com/amr-mostafa/KEYPAD4x4-MultipleKeypadMatrix-Driver-AVR/blob/master/keypad.h) file.
```
#define KEYPAD_DDR		DDRC						// KEYPAD port direction register
#define KEYPAD_PORT		PORTC						// KEYPAD port register
#define KEYPAD_PIN		PINC						// KEYPAD pin register
```

- Keypad matrices available:
```
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
```

# Testing and verification:
- All functions have been tested and verified on AVR Atmega16a microcontroller.

# Demo:
https://youtu.be/LmQw0ByxBPA

# COPYRIGHTS:
### Feel free to use all files in this project repository for purpose of #EDUCATION only.
### For any #COMMERCIAL or #NON_EDUCATIONAL use for any code in these files, please contact me at amr.mostaafaa@gmail.com
