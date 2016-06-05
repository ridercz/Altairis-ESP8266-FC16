#include <LedControlSPIESP8266.h>

#ifndef _FC16_h
#define _FC16_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class FC16 {

private:

	int _maxDevices;
	int _maxColumns;
	LedControl _lc;
	char* _text;
	int _textSize = 0;
	int _textColumns = 0;
	int _curCharIndex = 0;
	int _curCharBit = 0;
	bool _isScrolling = false;
	int _updateCount = 0;

	byte reverseBits(byte b);

public:

	FC16(int csPin, int numDevices = 1);

	int getColumnCount();

	int getTextColumns();

	void setColumn(int col, byte value);

	void setLed(int row, int col, bool state);

	void clearDisplay();

	void setIntensity(int intensity);

	void shutdown(bool status);

	void setText(char* text);

	void setBitmap(const byte* bitmap);

	bool update();

};

#endif

