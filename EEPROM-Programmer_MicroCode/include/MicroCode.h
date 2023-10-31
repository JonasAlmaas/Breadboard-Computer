#pragma once

#include <stdint.h>

class MicroCode
{
public:
	struct Specification
	{
		uint32_t HLT; // Halt
		uint32_t MI;  // Memory Address Register In
		uint32_t RI;  // RAM In
		uint32_t RO;  // RAM Out
		uint32_t II;  // Instruction Register In
		uint32_t IO;  // Instruction Register Out
		uint32_t AI;  // A Register In
		uint32_t AO;  // A Register Out
		uint32_t BI;  // B Register Out
		uint32_t EO;  // Sum Out (ΣO)
		uint32_t SU;  // Subtract
		uint32_t OI;  // Output Register In
		uint32_t PCI; // Program Counter In
		uint32_t PCO; // Program Counter Out
		uint32_t PCE; // Program Counter Enable
		uint32_t MCR; // Micro Instruction Counter Reset
		uint32_t SFE; // Status Flag Enable
	};

public:
	MicroCode(Specification spec);

	uint8_t GetByte(uint8_t instruction, uint8_t t, uint8_t flags, uint8_t eepromIndex) const;

private:
	Specification m_Spec;
	uint32_t m_Data[16][8];

};
