/*
 This example shows two strings, one printed using the standard string() function and the other stored in the internal flash memory using PROGMEM modifier
*/

#include <Nokia5110.h>

Nokia5110 lcd(7, 6, 5, 4, 3); // (PIN_SCE, PIN_RESET, PIN_DC, PIN_SDIN, PIN_SCLK)
// PIN_SDIN and PIN_SCLK should be driven by PWM enabled pins

char* hello[] PROGMEM = {"This is flash!"}; // string array stored in flash memory using PROGMEM modifier

void setup(void)
{
	lcd.init(); // init the LCD
}

void loop(void)
{
	lcd.clear();
	lcd.gotoXY(6, 2); // set marker to 16 pixels on x-axis, 2nd row
	lcd.string("Hello World!"); // print "Hello World!" string
	delay(1000);

	lcd.clear();
	lcd.gotoXY(0, 2);
	lcd.string(hello[0]); // print string array stored in flash memory
	delay(1000);
}
