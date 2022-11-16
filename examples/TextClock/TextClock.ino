/******************************************************************************
** TEXT SCROLL + CLOCK SAMPLE FOR ALTAIRIS ESP8266-FC16 LIBRARY
**
** This sample will scroll text on the display. Available characters are
** defined in FC16_Font.h. In addition to the ASCII table, the following glyphs
** are defined (inspired by CP437, but not fully compatible):
** \x01 :-)
** \x02 :-(
** \x03 heart
** \x04 diamond
** \x05 club
** \x06 spade
** \x07 bullet
** \x08 empty bullet
** \x09 big bullet
** \x0A big bullet inverse
** \x0B checkbox empty
** \x0C checkbox cross
** \x0D checkbox check
** \x0E checkbox full
** \x0F sunny
** \x10 triangle right
** \x11 triangle left
** \x18 arrow up
** \x19 arrow down
** \x1A arrow right
** \x1B arrow left
** \x7F full-width space (8 pixels)
**
** Hardware setup (ESP8266 <-> FC16):
** 5V <-> VCC, GND <-> GND, D7 <-> DIN, D8 <-> CS, D5 <-> CLK
******************************************************************************/

#include <FC16.h>
#include <TimeLib.h> // https://github.com/PaulStoffregen/Time

const int csPin = D8;			    // CS pin used to connect FC16
const int displayCount = 8;		// Number of displays; this sample requires 8
const int scrollDelay = 30;		// Scrolling speed - pause in ms

FC16 display = FC16(csPin, displayCount);

void setup() {
  display.begin();			    // turn on display
  display.setIntensity(8);	// set medium brightness
  display.clearDisplay();		// turn all LED off

  // Scrolling text to display on the first display (displays 0-3)
   display.setText("Hello, world!", 0, 3);
}

void loop() {
  // Perform scroll
  display.update();

  // Show clock on second display (displays 4-7, offset 32 from left)
  time_t currentTime = now();
  display.setClock(hour(currentTime), minute(currentTime), second(currentTime), 32);

  // Wait for 30 ms
  delay(scrollDelay);
}
