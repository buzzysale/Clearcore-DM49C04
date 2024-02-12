# Clearcore-DM49C04
This is a sample sketch to get the Teknic Clearcore working with the DM49C04 serial display. It  will likey work with other Arduino style chips with few modifications. 

This program reads an encoder and sends the position over serial and formats to display correctly on the DM49C04 display.  
The encoder is a 5-pin rotary type with A and B connected to the fast inputs (DI6 and DI7) on the ClearCore. 
And the encoder switch is attached to DI8. 
The clearcore encoder card is not neccessary. 
The DM49C04 Display is connected to the COM port via three pins. 
Clearcore COM Pins 4 (gnd to GND), 5(TX to RXD) and 6 (5v to VCC).
The other COM pins are not used. 

This inexpensive 4-digit, 7-segment display can be found online for about $1USD. 
The display recognizes other characters other than numbers for input.  Many of them are decoded in the image.  

The display has a 5 character input buffer.  However, it can only display 4 characters.  Remember this, because if you 
intend on sending it, say 8 characters, it will not rollover to display the last four, but will wrap around and you'll get
gunk.  It doesn't seem that special characters are counted against the input buffer.  

There are three special characters you can input (without quotes) into the serial buffer and it will cause special behavior: 
"%" will display as an empty character, but so will <space>. 
"*" will activate the . between the numbers.
"#" will activate the . between the numbers. 

