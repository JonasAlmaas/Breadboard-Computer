#include "EEPROM.h"

#include <Arduino.h>

EEPROM::EEPROM(EEPROM::Specification spec)
	: m_Spec(spec)
{
	pinMode(m_Spec.ShiftDataPin, OUTPUT);
	pinMode(m_Spec.ShiftClockPin, OUTPUT);
	pinMode(m_Spec.ShiftLatchPin, OUTPUT);

	// digitalWrite first to avoid accidental EEPROM writes
	digitalWrite(m_Spec.WriteEnablePin, HIGH); // Set pull-up resistor
	pinMode(m_Spec.WriteEnablePin, OUTPUT);

	setIOMode(IOMode::Write);
}

void EEPROM::setIOMode(EEPROM::IOMode mode)
{
	if (m_IOMode == mode || mode == IOMode::None) {
		return;
	}

	for (uint8_t pin = m_Spec.D0; pin <= m_Spec.D7; ++pin) {
		pinMode(pin, mode == IOMode::Read ? INPUT : OUTPUT);
	}

	m_IOMode = mode;
}

void EEPROM::setAddress(uint16_t address)
{
	shiftOut(m_Spec.ShiftDataPin, m_Spec.ShiftClockPin, MSBFIRST, (address >> 8) | m_IOMode);
	shiftOut(m_Spec.ShiftDataPin, m_Spec.ShiftClockPin, MSBFIRST, address);

	digitalWrite(m_Spec.ShiftLatchPin, LOW);
	digitalWrite(m_Spec.ShiftLatchPin, HIGH);
	digitalWrite(m_Spec.ShiftLatchPin, LOW);
}

uint8_t EEPROM::ReadByte(uint16_t address)
{
	setIOMode(IOMode::Read);
	setAddress(address);

	uint8_t data = 0;
	for (uint8_t pin = m_Spec.D7; pin >= m_Spec.D0; --pin) {
		pinMode(pin, INPUT);
		data |= digitalRead(pin) << (pin - m_Spec.D0);
	}

	return data;
}

void EEPROM::WriteByte(uint16_t address, uint8_t data)
{
	setIOMode(IOMode::Write);
	setAddress(address);

	for (uint8_t pin = m_Spec.D0; pin <= m_Spec.D7; ++pin) {
		digitalWrite(pin, (data >> (pin - m_Spec.D0)) & 0x1);
	}

	digitalWrite(m_Spec.WriteEnablePin, LOW);
	delayMicroseconds(1);
	digitalWrite(m_Spec.WriteEnablePin, HIGH);
	delay(1);
}

void EEPROM::WriteMicroCode(const MicroCode& microCode, uint8_t eepromIndex)
{
	Serial.print("Programming EEPROM");

	for (uint16_t address = 0; address < 512; ++address) {
		uint8_t flags       = (address & 0b110000000) >> 7;
		uint8_t instruction = (address & 0b001111000) >> 3;
		uint8_t t           = (address & 0b000000111);

		WriteByte(address, microCode.GetByte(instruction, t, flags, eepromIndex));

		if (address % 64 == 0) {
			Serial.print(".");
		}
	}

	Serial.println(" done");
}

void EEPROM::Dump(uint16_t start, uint16_t end)
{
	for (uint16_t base = start; base <= end; base += 16) {
		uint8_t data[16];
		for (uint8_t offset = 0; offset < 16; ++offset) {
			data[offset] = ReadByte(base + offset);
		}

		char buf[80];
		sprintf(buf, "%03x:   %02x %02x %02x %02x %02x %02x %02x %02x  %02x %02x %02x %02x %02x %02x %02x %02x",
			base, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10],
			data[11], data[12], data[13], data[14], data[15]);

		Serial.println(buf);
	}
}
