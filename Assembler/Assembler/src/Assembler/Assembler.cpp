#include "Assembler/Assembler.h"

#include <fstream>
#include <iostream>

namespace Utils {

	static std::string trim(const std::string& str, char character = ' ')
	{
		size_t first = str.find_first_not_of(character);
		if (first == std::string::npos) return "";
		size_t last = str.find_last_not_of(character);
		return str.substr(first, (last - first + 1));
	}
	
}

static std::unordered_map<std::string, uint8_t> opcodeTable = {
	{ "NOP", 0b0000 },
	{ "LDA", 0b0001 },
	{ "ADD", 0b0010 },
	{ "SUB", 0b0011 },
	{ "STA", 0b0100 },
	{ "LDI", 0b0101 },
	{ "JMP", 0b0110 },
	{ "OUT", 0b1110 },
	{ "HLT", 0b1111 },
};

Assembler::Assembler(const std::filesystem::path& path)
	: m_Path(path)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		m_Success = false;
		return;
	}

	std::string line;
	uint32_t lineNumber = 0;
	uint32_t address = 0;
	while (std::getline(file, line)) {
		line = Utils::trim(line);
		++lineNumber;

		AssemblyLine amsLine = {
			.DebugLine = false,
			.Address = 0,
			.LineNumber = lineNumber,
			.SourceCode = line,
			.MachineCode = 0,
		};
		
		line = line.substr(0, line.find_first_of(';')); // Remove comments
		line = Utils::trim(line);

		if (line.empty()) {
			continue;
		}

		size_t instructionSplitPos = line.find_first_of(' ');
		std::string instruction = line.substr(0, instructionSplitPos);

		// Check if the "instruction" is a label
		size_t labelPos = instruction.find_first_of(':');
		if (labelPos != std::string::npos) {
			std::string label = instruction.substr(0, labelPos);

			if (m_LabelTable.contains(label)) {
				std::cerr << "Error: Label redefinition on line " << lineNumber << std::endl;
				m_Success = false;
				return;
			}

			m_LabelTable.insert({ label, address });

			amsLine.DebugLine = true;
			m_Output.push_back(amsLine);

			continue;
		}

		if (!opcodeTable.contains(instruction)) {
			std::cerr << "Error: Invalid Assembly Instruction '" << instruction << "' on line " << lineNumber << std::endl;
			m_Success = false;
			return;
		}

		amsLine.Address = address++;
		amsLine.MachineCode = opcodeTable.at(instruction) << 4;

		if (instructionSplitPos != std::string::npos) {
			size_t argLength = line.find_first_of(' ', instructionSplitPos + 1) - instructionSplitPos - 1;
			std::string argument = line.substr(instructionSplitPos + 1, argLength);

			if (instruction == "JMP" && m_LabelTable.contains(argument)) {
				amsLine.MachineCode |= m_LabelTable.at(argument);
			}
			else {
				unsigned long value = std::stoul(argument);
				amsLine.MachineCode |= value & 0b1111;
			}
		}

		m_Output.push_back(amsLine);
	}

	file.close();
}
