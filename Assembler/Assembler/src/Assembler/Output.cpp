#include "Assembler/Output.h"

#include <fstream>
#include <iostream>

namespace Utils {

	static std::string binaryString(uint32_t value, uint8_t bitCount = 8, uint8_t tickOffset = 0) {
		char result[256];
		char* head = result;

		for (int i = bitCount - 1; i >= 0; i--) {
			if (tickOffset > 0
				&& (i + 1) % tickOffset == 0
				&& i != bitCount - 1) {
				*(head++) = '\'';
			}

			*(head++) = (value & (1 << i)) ? '1' : '0';
		}

		*head = '\0';
		
		return std::string(result);
	}
}

OutputFormat getOutputFormat(const Arguments& args)
{
	std::string outputFormat = args.Table.contains("-f")
		? args.Table.at("-f")
		: "B";

	if (outputFormat == "B") {
		return OutputFormat::Binary;
	}
	else if (outputFormat == "S") {
		return OutputFormat::BinaryString;
	}
	else if (outputFormat == "D") {
		return OutputFormat::Debug;
	}
	else {
		std::cerr << "Invalid output format '" << outputFormat << "'" << std::endl;
		return OutputFormat::Binary;
	}
}

std::filesystem::path getOutputPath(
	const Arguments& args,
	const std::filesystem::path& srcPath,
	OutputFormat outputFormat)
{
	if (args.Table.contains("-o")) {
		return std::filesystem::path(args.Table.at("-o"));
	}
	else {
		std::filesystem::path destPath = srcPath;

		switch (outputFormat)
		{
		case OutputFormat::Binary:
			destPath.replace_extension("bin");
			break;
		case OutputFormat::BinaryString:
			destPath.replace_extension("txt");
			break;
		case OutputFormat::Debug:
			destPath.replace_extension("debug");
			break;
		}

		return destPath;
	}
}

static void writeBinary(
	std::ofstream& file,
	const std::filesystem::path& path,
	const std::vector<AssemblyLine>& asmLines)
{
	for (AssemblyLine line : asmLines) {
		if (!line.DebugLine) {
			file.write((char*)&line.MachineCode, 1);
		}
	}
}

static void writeBinaryString(
	std::ofstream& file,
	const std::filesystem::path& path,
	const std::vector<AssemblyLine>& asmLines)
{
	for (AssemblyLine line : asmLines) {
		if (!line.DebugLine) {
			file << Utils::binaryString(line.MachineCode, 8) << "\n";
		}
	}
}

static void writeDebug(
	std::ofstream& file,
	const std::filesystem::path& path,
	const std::vector<AssemblyLine>& asmLines)
{
	uint32_t address = 0;
	for (AssemblyLine line : asmLines) {
		if (!line.DebugLine) {
			file <<
				Utils::binaryString(address++, 4) << " " <<
				Utils::binaryString(line.MachineCode, 8, 4) <<
				"        ";
		}
		else {
			file << "                      ";
		}

		file << line.LineNumber << ": " << line.SourceCode << '\n';
	}
}

void writeToFile(
	const std::filesystem::path& path,
	const std::vector<AssemblyLine>& asmLines,
	OutputFormat outputFormat)
{
	std::ofstream file(path);

	if (!file) {
		std::cerr << "Error opening file for writing" << std::endl;
		return;
	}

	switch (outputFormat)
	{
		case OutputFormat::Binary:          writeBinary(file, path, asmLines); break;
		case OutputFormat::BinaryString:    writeBinaryString(file, path, asmLines); break;
		case OutputFormat::Debug:           writeDebug(file, path, asmLines); break;
	}

	file.close();
}
