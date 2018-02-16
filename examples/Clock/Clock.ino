/******************************************************************************
** CLOCK SAMPLE FOR ALTAIRIS ESP8266-FC16 LIBRARY
**
** Hardware setup (ESP8266 <-> FC16):
** 5V <-> VCC, GND <-> GND, D7 <-> DIN, D8 <-> CS, D5 <-> CLK
******************************************************************************/

#include <FC16.h>
#include "TimeLib.h"

const int csPin = D8;						// CS pin used to connect FC16
const int displayCount = 4;					// Number of displays; usually 4 or 8
int lastSecond = -1;

FC16 display = FC16(csPin, displayCount);	// Define display parameters

void setup() {
	display.begin();			// turn on display
	display.setIntensity(8);	// set medium brightness
	display.clearDisplay();		// turn all LED off
}

void loop() {
	time_t currentTime = now();
	byte currentSecond = second(currentTime);
	if (currentSecond != lastSecond) {
		lastSecond = currentSecond;
		display.setClock(hour(currentTime), minute(currentTime), currentSecond);
	}
}
