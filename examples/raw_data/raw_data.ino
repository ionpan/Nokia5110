/*
 This example shows how you can write data directly to the LCD
*/

#include <Nokia5110.h>

Nokia5110 lcd(7, 6, 5, 4, 3); // (PIN_SCE, PIN_RESET, PIN_DC, PIN_SDIN, PIN_SCLK)
// PIN_SDIN and PIN_SCLK should be driven by PWM enabled pins

void setup(void)
{
	lcd.init(); // init the LCD
}

void loop(void)
{
	lcd.clear(); // clear the LCD
	// print a full line on rows 0, 2 and 4
	for (int row = 0; row < 6; row++) // select row
	{
		lcd.gotoXY(0, row); // take cursor to the beginning of the selected row
		for (int index = 0; index < 84; index++)
		{
			if (row % 2 == 0)
			{
				lcd.write(LCD_DATA, 0xFF); // fill with colour
			}
			else
			{
				lcd.write(LCD_DATA, 0x00); // leave blank
			}
		}
	}
	delay(1000);

	lcd.clear();
	// print a full line on rows 1, 3 and 5
	for (int row = 0; row < 6; row++) // select row
	{
		lcd.gotoXY(0, row); // take cursor to the beginning of the selected row
		for (int index = 0; index < 84; index++)
		{
			if (row % 2 == 0)
			{
				lcd.write(LCD_DATA, 0x00); // leave blank
			}
			else
			{
				lcd.write(LCD_DATA, 0xFF); // fill with colour
			}
		}
	}
	delay(1000);

}
