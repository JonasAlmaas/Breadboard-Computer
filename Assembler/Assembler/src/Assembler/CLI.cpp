#include "Assembler/CLI.h"

#include <iostream>

void cli_printHelp()
{
	std::cout << "Usage: Assembler [options] file.asm\n\n";
	std::cout << "  Options:\n";
	std::cout << "    -o <path>     Output file path.\n";
	std::cout << "    -f B|S|D      Output format.\n";
	std::cout << "      -f B            Binary (Default)\n";
	std::cout << "      -f S            Binary String\n";
	std::cout << "      -f D            Debug\n";

	std::cout << std::endl;
}
