# LedShowCapstoneProject

This is my computer science 30 project that uses the arduino uno r3, two buttons, and an addresable led strip (aka neopixel strip).

The program uses pin 0 on the arduino uno as its output pin which you connect to the data line of your led strip.
If you so desire you can change which pin is used as the output pin by changing the value of LedPin.

The program also uses pins 2 and 3 as the input pins for the buttons. These however cannot be changed as they are the only pins on the
arduino uno that are setup as interrupt pins.

