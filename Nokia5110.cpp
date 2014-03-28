/*
7-17-2011
Spark Fun Electronics 2011
Nathan Seidle
Modified on 03-12-2014 by ionpan

This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

*/

#include "Nokia5110.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

Nokia5110::Nokia5110(uint8_t _SCE, uint8_t _RESET, uint8_t _DC, uint8_t _SDIN, uint8_t _SCLK)
{
	SCE = _SCE;
	RESET = _RESET;
	DC = _DC;
	SDIN = _SDIN;
	SCLK = _SCLK;
	
	// configure control pins
	pinMode(SCE, OUTPUT);
	pinMode(RESET, OUTPUT);
	pinMode(DC, OUTPUT);
	pinMode(SDIN, OUTPUT);
	pinMode(SCLK, OUTPUT);
	
	// set default display values
	COLS = 84;
	ROWS = 48;
	mode = 0x0C; // set to normal
	contrast = 0xBC;
}

void Nokia5110::setContrast(uint16_t _contrast)
{
	contrast = _contrast;
}

void Nokia5110::setDimensions(int _COLS, int _ROWS)
{
	COLS = _COLS;
	ROWS = _ROWS;
}

void Nokia5110::invert()
{
	if (mode == 0x0C)
	{
		mode = 0x0D; // change to inverted
	}
	else if (mode == 0x0D)
	{
		mode = 0x0C; // change to normal
	}
}

void Nokia5110::gotoXY(int _x, int _y)
{
	write(0, 0x80 | _x);  // column.
	write(0, 0x40 | _y);  // row.  ?
}

// this takes a large array of bits and sends them to the LCD
void Nokia5110::bitmap(char _bitmapArray[])
{
	for (int index = 0; index < (COLS * ROWS / 8); index++)
	{
		write(LCD_DATA, _bitmapArray[index]);
	}
}

void Nokia5110::progBitmap(char _bitmapArray[])
{
	for (int index = 0; index < (COLS * ROWS / 8); index++)
	{
		write(LCD_DATA, pgm_read_byte(& _bitmapArray[index]));
	}
}

// This function takes in a character, looks it up in the font table/array
// And writes it to the screen
// Each character is 8 bits tall and 5 bits wide. We pad one blank column of
// pixels on the right side of the character for readability.
void Nokia5110::character(char _character)
{
	//LCDWrite(LCD_DATA, 0x00); // blank vertical line padding before character

	for (int index = 0; index < 5 ; index++)
	{
		write(LCD_DATA, pgm_read_byte(&(ASCII[_character - 0x20][index])));
	}
	//0x20 is the ASCII character for Space (' '). The font table starts with this character

	write(LCD_DATA, 0x00); // blank vertical line padding after character
}

// given a string of characters, one by one is passed to the LCD
void Nokia5110::string(char* _characters)
{
	while (*_characters)
	{
		character(*_characters++);
	}
}

// clears the LCD by writing zeros to the entire screen
void Nokia5110::clear(void)
{
	for (int index = 0; index < (COLS * ROWS / 8); index++)
	{
		write(LCD_DATA, 0x00);
	}

	gotoXY(0, 0); // after we clear the display, return to the home position
}

// this sends the magical commands to the PCD8544
void Nokia5110::init(void)
{
	// reset the LCD to a known state
	digitalWrite(RESET, LOW);
	digitalWrite(RESET, HIGH);

	write(LCD_COMMAND, 0x21); // tell LCD that extended commands follow
	write(LCD_COMMAND, contrast); // set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
	write(LCD_COMMAND, 0x04); // set Temp coefficent
	write(LCD_COMMAND, 0x14); // LCD bias mode 1:48: Try 0x13 or 0x14

	write(LCD_COMMAND, 0x20); // we must send 0x20 before modifying the display control mode
	write(LCD_COMMAND, mode); // set display control, normal mode. 0x0D for inverse
}

// There are two memory banks in the LCD, data/RAM and commands. This
// function sets the DC pin high or low depending, and then sends
// the data byte
void Nokia5110::write(byte _data_or_command, byte _data)
{
	digitalWrite(DC, _data_or_command); // tell the LCD that we are writing either to data or a command

	// send the data
	digitalWrite(SCE, LOW);
	shiftOut(SDIN, SCLK, MSBFIRST, _data);
	digitalWrite(SCE, HIGH);
}
