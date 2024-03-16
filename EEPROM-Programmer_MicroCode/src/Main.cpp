#include <Arduino.h>

#include "EEPROM.h"
#include "MicroCode.h"

#define BIT(x) (1ul << (x))

void programEEPROM(EEPROM& eeprom, const MicroCode& microCode)
{
	Serial.print("Programming EEPROM");

	for (uint16_t address = 0; address < 2048; ++address) {
		uint8_t segment     = (address & 0b11000000000) >> 9;
		uint8_t flags       = (address & 0b00110000000) >> 7;
		uint8_t instruction = (address & 0b00001111000) >> 3;
		uint8_t t           = (address & 0b00000000111);

		eeprom.WriteByte(address, microCode.GetByte(instruction, t, flags, segment));

		if (address % 32 == 0) {
			Serial.print(".");
		}
	}

	Serial.println("done");
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

	MicroCode microCode({
		.HLT = BIT(0),
		.MI  = BIT(1),
		.RI  = BIT(2),
		.RO  = BIT(3),
		.II  = BIT(4),
		.IO  = BIT(5),
		.AI  = BIT(6),
		.AO  = BIT(7),
		.BI  = BIT(8),
		.EO  = BIT(9),
		.SU  = BIT(10),
		.OI  = BIT(11),
		.PCI = BIT(12),
		.PCO = BIT(13),
		.PCE = BIT(14),
		.MCR = BIT(15),
		.SFE = BIT(16),
	});

	programEEPROM(eeprom, microCode);

	delay(100); // Wait after writing before reading

	eeprom.Dump(0, 512);

	return 0;
}
