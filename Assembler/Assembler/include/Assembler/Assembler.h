#pragma once

#include "Assembler/Arguments.h"

#include <filesystem>

struct AssemblyLine
{
	bool DebugLine;
	uint32_t Address;
	int32_t LineNumber;
	std::string SourceCode;
	uint8_t MachineCode;
};

class Assembler
{
public:
	Assembler(const std::filesystem::path& path);

	bool Success() const { return m_Success; }

	const std::vector<AssemblyLine>& GetOutput() const
	{
		return m_Output;
	}

private:
	bool m_Success = true;
	
	std::filesystem::path m_Path;

	std::vector<AssemblyLine> m_Output;
	
};
