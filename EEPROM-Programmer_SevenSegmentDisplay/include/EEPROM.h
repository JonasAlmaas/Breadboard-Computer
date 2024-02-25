#pragma once

#include <stdint.h>

class EEPROM
{
public:
	struct Specification
	{
		uint8_t ShiftDataPin;
		uint8_t ShiftClockPin;
		uint8_t ShiftLatchPin;
		uint8_t D0;
		uint8_t D7;
		uint8_t WriteEnablePin;
	};

private:
	enum IOMode
	{
		None = 0xFF,
		Read = 0x0,
		Write = 0x80,
	};

public:
	EEPROM(Specification spec);

	uint8_t ReadByte(uint16_t address);
	void WriteByte(uint16_t address, uint8_t data);

	/**
	 * @brief Dumps the EEPROM contents to the serial port in chunks of 16 bytes.
	*/
	void Dump(uint16_t start = 0, uint16_t end = 2047);

private:
	void setIOMode(IOMode mode);
	void setAddress(uint16_t address);

private:
	Specification m_Spec;
	IOMode m_IOMode = IOMode::None;

};
