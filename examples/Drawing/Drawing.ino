/******************************************************************************
** DRAWING SAMPLE FOR ALTAIRIS ESP8266-FC16 LIBRARY
**
** This sample will turn on all LEDs on matrix display one by one and then
** turn then off again.
**
** Hardware setup (ESP8266 <-> FC16):
** 3V3 <-> VCC, GND <-> GND, D7 <-> DIN, D8 <-> CS, D5 <-> CLK
******************************************************************************/

#include <FC16.h>

const int csPin = D8;						// CS pin used to connect FC16
const int displayCount = 4;					// Number of displays; usually 4 or 8
const int wait = 30;						// Delay between steps (ms)

FC16 display = FC16(csPin, displayCount);	// Define display parameters
bool ledState = true;						// LED state for next run

void setup() {
	display.shutdown(false);	// turn on display
	display.setIntensity(8);	// set medium brightness
	display.clearDisplay();		// turn all LED off
}

void loop() {
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8 * displayCount; col++) {
			// Set LED state on/off for given row, column
			display.setLed(row, col, ledState);

			// Wait for a while
			delay(wait);
		}
	}

	// Switch desired LED state
	ledState = !ledState;
}
