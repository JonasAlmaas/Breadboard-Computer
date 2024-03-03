#include "Programmer/CLI.h"

#include <iostream>

void cli_printHelp()
{
	std::cout << "Usage: Programmer [options] file.asm\n\n";
	std::cout << "  Options:\n";
	std::cout << "    -p <COMPort>     COM part (Example: \"COM3\").\n";

	std::cout << std::endl;
}
