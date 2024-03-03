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

	static std::string trimWhitespace(const std::string& str)
	{
		return Utils::trim(Utils::trim(Utils::trim(str, ' '), '\t'), '\n');
	}

	static bool isNumeric(const std::string& str)
	{
		return !str.empty() && std::find_if(str.begin(), str.end(), [](char c) { return !std::isdigit(c); }) == str.end();
	}
	
}

struct OpcodeInfo {
	uint8_t opcode;
	bool hasArgument;
};

static std::unordered_map<std::string, OpcodeInfo> opcodeTable = {
	{ "NOP", { 0b0000, false }}, // 0000'xxxx
	{ "LDA", { 0b0001, true }},  // 0001'xxxx'kkkk'kkkk
	{ "ADD", { 0b0010, true }},  // 0010'xxxx'kkkk'kkkk
	{ "SUB", { 0b0011, true }},  // 0011'xxxx'kkkk'kkkk
	{ "STA", { 0b0100, true }},  // 0100'xxxx'kkkk'kkkk
	{ "LDI", { 0b0101, true }},  // 0101'xxxx'KKKK'KKKK
	{ "JMP", { 0b0110, true }},  // 0110'xxxx'kkkk'kkkk
	{ "JC",  { 0b0111, true }},  // 0111'xxxx'kkkk'kkkk
	{ "JZ",  { 0b1000, true }},  // 1000'xxxx'kkkk'kkkk
	{ "OUT", { 0b1110, false }}, // 1110'xxxx'
	{ "HLT", { 0b1111, false }}, // 1111'xxxx
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

	std::unordered_map<std::string, uint8_t> labelTable;

	std::string line;
	int32_t lineNumber = 0;
	uint32_t address = 0;
	while (std::getline(file, line)) {
		line = Utils::trimWhitespace(line);
		
		AssemblyLine amsLine = {
			.DebugLine = false,
			.Address = 0,
			.LineNumber = ++lineNumber,
			.SourceCode = line,
			.MachineCode = 0,
		};

		bool hasComment = line.find_first_of(';') != std::string::npos;

		line = line.substr(0, line.find_first_of(';')); // Remove comments
		line = Utils::trimWhitespace(line);

		if (line.empty()) {
			if (hasComment) {
				amsLine.DebugLine = true;
				m_Output.push_back(amsLine);
			}
			
			continue;
		}
		
		size_t instructionSplitPos = line.find_first_of(' ');
		std::string instruction = line.substr(0, instructionSplitPos);

		// Check if the "instruction" is a label
		size_t labelPos = instruction.find_first_of(':');
		if (labelPos != std::string::npos) {
			std::string label = instruction.substr(0, labelPos);

			if (labelTable.contains(label)) {
				std::cerr << "Error: Label redefinition on line " << lineNumber << std::endl;
				m_Success = false;
				return;
			}

			labelTable.insert({ label, address });

			amsLine.DebugLine = true;
			m_Output.push_back(amsLine);

			continue;
		}

		if (!opcodeTable.contains(instruction)) {
			std::cerr << "Error: Invalid Assembly Instruction '" << instruction << "' on line " << lineNumber << std::endl;
			m_Success = false;
			return;
		}

		const OpcodeInfo& opcodeInfo = opcodeTable[instruction];

		amsLine.Address = address++;
		amsLine.MachineCode = opcodeInfo.opcode << 4;
		// For now, the first byte always only uses the 4 most significant bits
		
		m_Output.push_back(amsLine);

		if (opcodeInfo.hasArgument) {
			AssemblyLine amsLine2 = {
				.DebugLine = false,
				.Address = address++,
				.LineNumber = -1,
				.SourceCode = "",
				.MachineCode = 0,
			};

			if (instructionSplitPos != std::string::npos) {
				size_t argLength = line.find_first_of(' ', instructionSplitPos + 1) - instructionSplitPos - 1;
				std::string argument = line.substr(instructionSplitPos + 1, argLength);

				if ((instruction == "JMP" || instruction == "JC" || instruction == "JZ") && labelTable.contains(argument)) {
					amsLine2.MachineCode = labelTable.at(argument);
				} else if (Utils::isNumeric(argument)) {
					amsLine2.MachineCode = (uint8_t)(std::stoul(argument) & 0xff);
				} else {
					std::cerr << "Error: Invalid argument '" << argument << "' on line " << lineNumber << std::endl;
					m_Success = false;
					return;
				}
			}

			m_Output.push_back(amsLine2);
		}
	}

	file.close();
}
