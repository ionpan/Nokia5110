This code writes a series of images and text to the Nokia 5110 84x48 graphic LCD:
http://www.sparkfun.com/products/10168

It is based on an example for the Nokia 5110 LCD module, which was written by Nathan Seidle:
http://dlnmh9ip6v2uc.cloudfront.net/datasheets/LCD/Monochrome/Nokia_5110_Example.pde

I converted it to an Arduino library, with an accompanying example. Also saved 480Bytes of SRAM.

Features:
 * ASCII characters' HEX values array is stored in flash memory
 * Support to set device pinout
 * Support to set screen dimensions in pixels
 * Support to set screen contrast
 * Support to change screen mode right through sketch (normal or inverted)
 * Support to display bitmap arrays stored in flash memory (using PROGMEM modifier)
 * Support for older Arduino IDE versions (<1.0)


Original release notes:
7-17-2011
Spark Fun Electronics 2011
Nathan Seidle
Modified on 12-2014 by ionpan

This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).


#### Warning - About the Nokia 5110 LCD:

Do not drive the backlight with 5V. It will smoke. However, the backlight on the LCD seems to be
happy with direct drive from the 3.3V regulator.

Although the PCD8544 controller datasheet recommends 3.3V, the graphic Nokia 5110 LCD can run at 3.3V or 5V.
No resistors needed on the signal lines.

You will need 5 signal lines to connect to the LCD, 3.3 or 5V for power, 3.3V for LED backlight, and 1 for ground.
