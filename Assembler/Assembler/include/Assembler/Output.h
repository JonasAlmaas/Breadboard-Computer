#pragma once

#include <filesystem>
#include <vector>

#include "Arguments.h"
#include "Assembler.h"

enum OutputFormat {
	Binary,
	BinaryString,
	Debug,
};

OutputFormat getOutputFormat(const Arguments& args);

std::filesystem::path getOutputPath(const Arguments& args, const std::filesystem::path& srcPath, OutputFormat outputFormat);

void writeToFile(const std::filesystem::path& path, const std::vector<AssemblyLine>& asmLines, OutputFormat outputFormat);
