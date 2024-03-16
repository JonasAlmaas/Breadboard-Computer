#include <Arduino.h>
#include <stdlib.h>

#include "EEPROM.h"

// -- Input / Address --
enum {
	// A0-A7 - 8 bit data

	// A8-A9 Displays
	Disp0 = 0,		// Sign bit
	Disp1 = 0b01 << 8,	// Hundreds
	Disp2 = 0b10 << 8,	// Tens
	Disp3 = 0b11 << 8,	// Ones

	// A10 - Sign bit
	TwosComp = 0b1 << 10,	// 0 = Unsigned, 1 = Twos Complement
};

// -- Output --
enum {
	// Segments
	SegA = 0b10000000,	// Center
	SegB = 0b01000000,	// Left Top
	SegC = 0b00100000,	// Top
	SegD = 0b00010000,	// Right Top
	SegE = 0b00001000,	// Left Bottom
	SegF = 0b00000001,	// Bottom
	SegG = 0b00000010,	// Right Bottom
	SegDP = 0b00000100,	// Decimal Point (Not used)
};

/// @brief Takes in a number between 0 and 9
/// @return The value used to be displayed on a 7-segment display
static uint8_t getSegValueFromNumber(uint8_t value)
{
	switch (value)
	{
		case 0: return SegB | SegC | SegD | SegE | SegF | SegG;
		case 1: return SegD | SegG;
		case 2: return SegC | SegD | SegA | SegE | SegF;
		case 3: return SegC | SegD | SegA | SegG | SegF;
		case 4: return SegB | SegA | SegD | SegG;
		case 5: return SegC | SegB | SegA | SegG | SegF;
		case 6: return SegC | SegB | SegA | SegE | SegF | SegG;
		case 7: return SegC | SegD | SegG;
		case 8: return SegA | SegB | SegC | SegD | SegE | SegF | SegG;
		case 9: return SegA | SegB | SegC | SegD | SegF | SegG;
		default: return 0;
	}
}

void programEEPROM(EEPROM& eeprom)
{
	for (uint16_t i = 0; i <= 255; ++i) {
		Serial.print(".");

		eeprom.WriteByte(i | Disp0, 0);
		eeprom.WriteByte(i | Disp1, getSegValueFromNumber(i / 100));
		eeprom.WriteByte(i | Disp2, getSegValueFromNumber((i / 10) % 10));
		eeprom.WriteByte(i | Disp3, getSegValueFromNumber(i % 10));

		// Signed Values
		int16_t sv = (int16_t)i - 128;
		uint8_t absSV = abs(sv);
		eeprom.WriteByte((byte)sv | TwosComp | Disp0, sv < 0 ? SegA : 0);
		eeprom.WriteByte((byte)sv | TwosComp | Disp1, getSegValueFromNumber(absSV / 100));
		eeprom.WriteByte((byte)sv | TwosComp | Disp2, getSegValueFromNumber((absSV / 10) % 10));
		eeprom.WriteByte((byte)sv | TwosComp | Disp3, getSegValueFromNumber(absSV % 10));
	}
}

int main()
{
	init(); // Required for Arduino to work

	Serial.begin(57600);

	EEPROM eeprom({
		.ShiftDataPin = 2,
		.ShiftClockPin = 3,
		.ShiftLatchPin = 4,
		.D0 = 5,
		.D7 = 12,
		.WriteEnablePin = 13,
	});

	Serial.print("Programming EEPROM");
	programEEPROM(eeprom);
	Serial.println("\nProgramming complete\nReading EEPROM");

	delay(100); // Wait after writing before reading

	eeprom.Dump();

	return 0;
}
