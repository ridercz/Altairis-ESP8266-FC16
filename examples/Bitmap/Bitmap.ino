/******************************************************************************
** BITMAP SAMPLE FOR ALTAIRIS ESP8266-FC16 LIBRARY
**
** This sample will show the setBitmap function. This function expects byte[]
** array as input. Every item is single column (left to right), with most
** significant bit on top.
**
** Hardware setup (ESP8266 <-> FC16):
** 3V3 <-> VCC, GND <-> GND, D7 <-> DIN, D8 <-> CS, D5 <-> CLK
******************************************************************************/

#include <FC16.h>

const int csPin = D8;						// CS pin used to connect FC16
const int displayCount = 4;					// Number of displays; usually 4 or 8

const byte BMP_4D[] = {									// >HELLO< for 4-matrix configuration
	0xFF, 0x7E, 0x3C, 0x18, 0x00, 0x7E, 0x08, 0x08,		// Matrix 1
	0x7E, 0x00, 0x7E, 0x4A, 0x4A, 0x42, 0x00, 0x7E,		// Matrix 2
	0x40, 0x40, 0x00, 0x7E, 0x40, 0x40, 0x00, 0x3C,		// Matrix 3
	0x42, 0x42, 0x3C, 0x00, 0x18, 0x3C, 0x7E, 0xFF };	// Matrix 4
const byte BMP_8D[] = {									// >HELLO WORLD< for 8-matrix configuration
	0xFF, 0x7E, 0x3C, 0x18, 0x00, 0x7E, 0x08, 0x08,		// Matrix 1
	0x7E, 0x00, 0x7E, 0x4A, 0x4A, 0x42, 0x00, 0x7E,		// Matrix 2
	0x40, 0x40, 0x40, 0x00, 0x7E, 0x40, 0x40, 0x40,		// Matrix 3
	0x00, 0x3C, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,		// Matrix 4
	0x00, 0x00, 0x3E, 0x40, 0x30, 0x40, 0x3E, 0x00,		// Matrix 5
	0x3C, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x7E, 0x12,		// Matrix 6
	0x32, 0x4C, 0x00, 0x7E, 0x40, 0x40, 0x00, 0x7E,		// Matrix 7
	0x42, 0x42, 0x3C, 0x00, 0x18, 0x3C, 0x7E, 0xFF };	// Matrix 8

FC16 display = FC16(csPin, displayCount);	// Define display parameters

void setup() {
	display.shutdown(false);	// turn on display
	display.setIntensity(8);	// set medium brightness
	display.clearDisplay();		// turn all LED off

	if (displayCount <= 4) {
		// Show sample bitmap for 4 displays
		display.setBitmap(BMP_4D);
	} else {
		// Show sample bitmap for 8 displays
		display.setBitmap(BMP_8D);
	}
}

void loop() {

}
