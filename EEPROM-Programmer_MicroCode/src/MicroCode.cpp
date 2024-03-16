#include "MicroCode.h"

#include <string.h>

enum SRegFlags {
	Carry = 1 << 0,
	Zero  = 1 << 1,
};

enum Instructions {
	NOP = 0b0000,
	LDA = 0b0001,
	ADD = 0b0010,
	SUB = 0b0011,
	STA = 0b0100,
	LDI = 0b0101,
	JMP = 0b0110,
	JC  = 0b0111,
	JZ  = 0b1000,
	// Space for expansion
	OUT = 0b1110,
	HLT = 0b1111,
};

MicroCode::MicroCode(MicroCode::Specification s)
	: m_Spec(s)
{
	memset(m_Data, 0, sizeof m_Data);

	// 0000 - NOP - No Operation
	m_Data[Instructions::NOP][0] = s.PCO|s.MI;
	m_Data[Instructions::NOP][1] = s.RO|s.II|s.PCE;
	m_Data[Instructions::NOP][2] = s.MCR;

	// 0001 - LDA - Load A
	m_Data[Instructions::LDA][0] = s.PCO|s.MI;
	m_Data[Instructions::LDA][1] = s.RO|s.II|s.PCE;
	m_Data[Instructions::LDA][2] = s.PCO|s.MI|s.PCE;
	m_Data[Instructions::LDA][3] = s.RO|s.MI;
	m_Data[Instructions::LDA][4] = s.RO|s.AI;
	m_Data[Instructions::LDA][5] = s.MCR;

 	// 0010 - ADD - Add
	m_Data[Instructions::ADD][0] = s.PCO|s.MI;
	m_Data[Instructions::ADD][1] = s.RO|s.II|s.PCE;
	m_Data[Instructions::ADD][2] = s.PCO|s.MI|s.PCE;
	m_Data[Instructions::ADD][3] = s.RO|s.MI;
	m_Data[Instructions::ADD][4] = s.RO|s.BI;
	m_Data[Instructions::ADD][5] = s.EO|s.AI|s.SFE;
	m_Data[Instructions::ADD][6] = s.MCR;

	// 0011 - SUB - Subtract
	m_Data[Instructions::SUB][0] = s.PCO|s.MI;
	m_Data[Instructions::SUB][1] = s.RO|s.II|s.PCE;
	m_Data[Instructions::SUB][2] = s.PCO|s.MI|s.PCE;
	m_Data[Instructions::SUB][3] = s.RO|s.MI;
	m_Data[Instructions::SUB][4] = s.RO|s.BI|s.SU;
	m_Data[Instructions::SUB][5] = s.SU|s.EO|s.AI|s.SFE;
	m_Data[Instructions::SUB][6] = s.MCR;

	// 0100 - STA - Store A
	m_Data[Instructions::STA][0] = s.PCO|s.MI;
	m_Data[Instructions::STA][1] = s.RO|s.II|s.PCE;
	m_Data[Instructions::STA][2] = s.PCO|s.MI|s.PCE;
	m_Data[Instructions::STA][3] = s.RO|s.MI;
	m_Data[Instructions::STA][4] = s.AO|s.RI;
	m_Data[Instructions::STA][5] = s.MCR;

	// 0101 - LDI - Load Immediate
	m_Data[Instructions::LDI][0] = s.PCO|s.MI;
	m_Data[Instructions::LDI][1] = s.RO|s.II|s.PCE;
	m_Data[Instructions::LDI][2] = s.PCO|s.MI|s.PCE;
	m_Data[Instructions::LDI][3] = s.RO|s.AI;
	m_Data[Instructions::LDI][4] = s.MCR;

	// 0110 - JMP - Jump
	m_Data[Instructions::JMP][0] = s.PCO|s.MI;
	m_Data[Instructions::JMP][1] = s.RO|s.II|s.PCE;
	m_Data[Instructions::JMP][2] = s.PCO|s.MI|s.PCE;
	m_Data[Instructions::JMP][3] = s.RO|s.PCI;
	m_Data[Instructions::JMP][4] = s.MCR;

	// 0111 - JC  - Jump if Carry
	m_Data[Instructions::JC][0] = s.PCO|s.MI;
	m_Data[Instructions::JC][1] = s.RO|s.II|s.PCE;
	m_Data[Instructions::JC][2] = s.PCO|s.MI|s.PCE; // This gets modified dynamically in GetByte()
	m_Data[Instructions::JC][3] = s.RO|s.PCI;
	m_Data[Instructions::JC][4] = s.MCR;

	// 1000 - JZ  - Jump if Zero
	m_Data[Instructions::JZ][0] = s.PCO|s.MI;
	m_Data[Instructions::JZ][1] = s.RO|s.II|s.PCE;
	m_Data[Instructions::JZ][2] = s.PCO|s.MI|s.PCE; // This gets modified dynamically in GetByte()
	m_Data[Instructions::JZ][3] = s.RO|s.PCI;
	m_Data[Instructions::JZ][4] = s.MCR;

	// 1001
	m_Data[0b1001][0] = s.PCO|s.MI;
	m_Data[0b1001][1] = s.RO|s.II|s.PCE;
	m_Data[0b1001][2] = s.MCR;

	// 1010
	m_Data[0b1010][0] = s.PCO|s.MI;
	m_Data[0b1010][1] = s.RO|s.II|s.PCE;
	m_Data[0b1010][2] = s.MCR;

	// 1011
	m_Data[0b1011][0] = s.PCO|s.MI;
	m_Data[0b1011][1] = s.RO|s.II|s.PCE;
	m_Data[0b1011][2] = s.MCR;

	// 1100
	m_Data[0b1100][0] = s.PCO|s.MI;
	m_Data[0b1100][1] = s.RO|s.II|s.PCE;
	m_Data[0b1100][2] = s.MCR;

	// 1101
	m_Data[0b1101][0] = s.PCO|s.MI;
	m_Data[0b1101][1] = s.RO|s.II|s.PCE;
	m_Data[0b1101][2] = s.MCR;

	// 1110 - OUT - Output
	m_Data[Instructions::OUT][0] = s.PCO|s.MI;
	m_Data[Instructions::OUT][1] = s.RO|s.II|s.PCE;
	m_Data[Instructions::OUT][2] = s.AO|s.OI;
	m_Data[Instructions::OUT][3] = s.MCR;

	// 1111 - HLT - Halt
	m_Data[Instructions::HLT][0] = s.PCO|s.MI;
	m_Data[Instructions::HLT][1] = s.RO|s.II|s.PCE;
	m_Data[Instructions::HLT][2] = s.HLT;
}

uint8_t MicroCode::GetByte(uint8_t instruction, uint8_t t, uint8_t flags, uint8_t segment) const
{
	uint32_t value = m_Data[instruction][t];

	// Modify the microcode based on the flags
	if (t == 2) {
		if ((instruction == Instructions::JC && !(flags & SRegFlags::Carry))
				|| (instruction == Instructions::JZ && !(flags & SRegFlags::Zero))) {
			value = m_Spec.PCE|m_Spec.MCR;
		}
	}

	return (uint8_t)(value >> (8 * segment));
}
