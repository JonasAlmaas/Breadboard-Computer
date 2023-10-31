#include <Arduino.h>

#include "EEPROM.h"

#define BIT(x) (1ul << (x))

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

	eeprom.WriteMicroCode(microCode, 0);

	delay(10); // Wait after writing before reading

	eeprom.Dump(0, 511);

	return 0;
}
