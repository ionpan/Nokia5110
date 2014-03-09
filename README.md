This code is based on an example for the Nokia 5110 LCD module, which was written by Nathan Seidle.
(http://dlnmh9ip6v2uc.cloudfront.net/datasheets/LCD/Monochrome/Nokia_5110_Example.pde)
I found it really practical to display text on my LCD and it also takes so little space.
So I created the .cpp and .h files based on the functions included in his example, in order to implementate
in some of my projects, and thought to share with you guys as I found it really useful. Also, I managed to
optimize it a bit by allocating the characters' HEX values to the flash memory instead of SRAM. No big of
a deal but should save you 480Byte of SRAM.

Thank you Nathan

ionpan


Original release notes:
7-17-2011
Spark Fun Electronics 2011
Nathan Seidle
This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

This code writes a series of images and text to the Nokia 5110 84x48 graphic LCD:
http://www.sparkfun.com/products/10168

Do not drive the backlight with 5V. It will smoke. However, the backlight on the LCD seems to be
happy with direct drive from the 3.3V regulator.

Although the PCD8544 controller datasheet recommends 3.3V, the graphic Nokia 5110 LCD can run at 3.3V or 5V.
No resistors needed on the signal lines.

You will need 5 signal lines to connect to the LCD, 3.3 or 5V for power, 3.3V for LED backlight, and 1 for ground.