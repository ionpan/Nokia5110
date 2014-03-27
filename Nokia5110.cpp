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

Nokia5110::Nokia5110(uint8_t SCE, uint8_t RESET, uint8_t DC, uint8_t SDIN, uint8_t SCLK)
{
	_SCE = SCE;
	_RESET = RESET;
	_DC = DC;
	_SDIN = SDIN;
	_SCLK = SCLK;
	_COLS = 84;
	_ROWS = 48;
	_mode = 0x0C; // init to normal
	_contrast = 0xBC;
}

void Nokia5110::setContrast(uint16_t contrast)
{
	_contrast = contrast;
}

void Nokia5110::setDimensions(int COLS, int ROWS)
{
	_COLS = COLS;
	_ROWS = ROWS;
}

void Nokia5110::invert()
{
	if (_mode == 0x0C)
	{
		_mode = 0x0D; // change to inverted
	}
	else if (_mode == 0x0D)
	{
		_mode = 0x0C; // change to normal
	}
}

void Nokia5110::gotoXY(int x, int y)
{
	write(0, 0x80 | x);  // Column.
	write(0, 0x40 | y);  // Row.  ?
}

//This takes a large array of bits and sends them to the LCD
void Nokia5110::bitmap(char bitmapArray[])
{
	for (int index = 0; index < (_COLS * _ROWS / 8); index++)
	{
		write(LCD_DATA, bitmapArray[index]);
	}
}

void Nokia5110::progBitmap(char bitmapArray[])
{
	for (int index = 0; index < (_COLS * _ROWS / 8); index++)
	{
		write(LCD_DATA, pgm_read_byte(& bitmapArray[index]));
	}
}

//This function takes in a character, looks it up in the font table/array
//And writes it to the screen
//Each character is 8 bits tall and 5 bits wide. We pad one blank column of
//pixels on each side of the character for readability.
void Nokia5110::character(char character)
{
	//LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding before character

	for (int index = 0; index < 5 ; index++)
	{
		write(LCD_DATA, pgm_read_byte(&(ASCII[character - 0x20][index])));
	}
	//0x20 is the ASCII character for Space (' '). The font table starts with this character

	write(LCD_DATA, 0x00); //Blank vertical line padding after character
}

//Given a string of characters, one by one is passed to the LCD
void Nokia5110::string(char* characters)
{
	while (*characters)
	{
		character(*characters++);
	}
}

//Clears the LCD by writing zeros to the entire screen
void Nokia5110::clear(void)
{
	for (int index = 0; index < (_COLS * _ROWS / 8); index++)
	{
		write(LCD_DATA, 0x00);
	}

	gotoXY(0, 0); //After we clear the display, return to the home position
}

//This sends the magical commands to the PCD8544
void Nokia5110::init(void)
{

	//Configure control pins
	pinMode(_SCE, OUTPUT);
	pinMode(_RESET, OUTPUT);
	pinMode(_DC, OUTPUT);
	pinMode(_SDIN, OUTPUT);
	pinMode(_SCLK, OUTPUT);

	//Reset the LCD to a known state
	digitalWrite(_RESET, LOW);
	digitalWrite(_RESET, HIGH);

	write(LCD_COMMAND, 0x21); //Tell LCD that extended commands follow
	write(LCD_COMMAND, _contrast); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
	write(LCD_COMMAND, 0x04); //Set Temp coefficent
	write(LCD_COMMAND, 0x14); //LCD bias mode 1:48: Try 0x13 or 0x14

	write(LCD_COMMAND, 0x20); //We must send 0x20 before modifying the display control mode
	write(LCD_COMMAND, _mode); //Set display control, normal mode. 0x0D for inverse
}

//There are two memory banks in the LCD, data/RAM and commands. This
//function sets the DC pin high or low depending, and then sends
//the data byte
void Nokia5110::write(byte data_or_command, byte data)
{
	digitalWrite(_DC, data_or_command); //Tell the LCD that we are writing either to data or a command

	//Send the data
	digitalWrite(_SCE, LOW);
	shiftOut(_SDIN, _SCLK, MSBFIRST, data);
	digitalWrite(_SCE, HIGH);
}