#include "FC16.h"
#include "FC16_Font.h"

FC16::FC16(int csPin, int numDevices)
	: _lc(csPin, numDevices) {
	_maxDevices = _lc.getDeviceCount();
	_maxColumns = _maxDevices * 8;
}

int FC16::getColumnCount() {
	return _maxColumns;
}

int FC16::getTextColumns() {
	return _textColumns;
}

void FC16::setColumn(int col, byte value) {
	if (col < 0) col = 0;
	if (col >= _maxColumns) col = _maxColumns - 1;

	int addr = _maxDevices - 1 - col / 8;
	int phyCol = col % 8;

	_lc.setColumn(addr, phyCol, reverseBits(value));
	_isScrolling = false;
}

void FC16::setLed(int row, int col, bool state) {
	if (row < 0) row = 0;
	if (row > 7) row = 7;
	if (col < 0) col = 0;
	if (col >= _maxColumns) col = _maxColumns - 1;

	int addr = _maxDevices - 1 - col / 8;
	int phyCol = col % 8;

	_lc.setLed(addr, row, phyCol, state);
	_isScrolling = false;
}

void FC16::clearDisplay() {
	for (int i = 0; i < _maxDevices; i++) {
		_lc.clearDisplay(i);
	}
	_isScrolling = false;
}

void FC16::setIntensity(int intensity) {
	if (intensity < 0) intensity = 0;
	if (intensity > 15) intensity = 15;

	for (int i = 0; i < _maxDevices; i++) {
		_lc.setIntensity(i, intensity);
	}
}

void FC16::shutdown(bool status) {
	for (int i = 0; i < _maxDevices; i++) {
		_lc.shutdown(i, status);
	}
}

void FC16::setText(char* text) {
	_textSize = strlen(text) + _maxDevices;
	_text = (char*)malloc(_textSize + 1);
	strcpy(_text, text);

	// Add the same number of full width spaces as we have displays
	_text[_textSize] = '\0';
	for (int i = _textSize - 1; i >= strlen(text); i--) {
		_text[i] = '\x7F';
	}

	// Compute number of columns
	_textColumns = _textSize;						// start with number of 1-px spaces between letters
	for (int i = 0; i < _textSize; i++) {
		_textColumns += FONT_LENGTHS[_text[i]];		// Add letter width
	}

	_isScrolling = true;
}

void FC16::setBitmap(const byte* bitmap) {
	for (byte i = 0; i < _maxColumns; i++) {
		setColumn(i, bitmap[i]);
	}
	_isScrolling = false;
}

bool FC16::update() {
	if (!_isScrolling) return false;

	int curCharIndexSave2 = _curCharIndex;
	int curCharBitSave2 = _curCharBit;
	char curChar;

	for (int addr = _maxDevices - 1; addr >= 0; addr--) {
		// Set up rows on current  display
		for (int row = 0; row < 8; row++) {
			byte outputByte = 0;
			curChar = _text[_curCharIndex];
			int curCharIndexSave = _curCharIndex;
			int curCharBitSave = _curCharBit;

			// Copy over data for 8 columns to current row and send it to current display
			for (int k = 7; k >= 0; k--) {
				// This byte is the bitmap of the current character for the current row
				byte currentcharbits = FONT_GLYPHS[((curChar) * 8) + row];
				if (currentcharbits & (1 << _curCharBit)) outputByte |= (1 << k);

				// Advance the current character bit of current character
				_curCharBit++;

				// We are past the end of this character, so advance.
				if (_curCharBit > FONT_LENGTHS[curChar]) {
					_curCharBit = 0;
					_curCharIndex += 1;
					if (_curCharIndex + 1 > _textSize) {
						_curCharIndex = 0;
					}
					curChar = _text[_curCharIndex];
				}
			}

			// Display row
			_lc.setRow(addr, row, outputByte);

			// If this is not the last row, roll back advancement, if it is, leave the counters advanced.
			if (row != 7) {
				_curCharIndex = curCharIndexSave;
				_curCharBit = curCharBitSave;
			}
		}
	}

	_curCharIndex = curCharIndexSave2;
	_curCharBit = curCharBitSave2;
	curChar = _text[_curCharIndex];

	// advance the current character bit of current character
	_curCharBit++;

	if (_curCharBit > FONT_LENGTHS[curChar]) {
		// we are past the end of this character, so advance.
		_curCharBit = 0;
		_curCharIndex += 1;
		if (_curCharIndex + 1 > _textSize) {
			_curCharIndex = 0;
		}
	}

	// Check if animation finished
	bool done = false;
	_updateCount++;
	if (_updateCount == _textColumns - 8 * _maxDevices) {
		// Animation completed - displaying just empty end spaces
		done = true;
	}
	if (_updateCount == _textColumns) _updateCount = 0;

	return done;
}

byte FC16::reverseBits(byte b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}
