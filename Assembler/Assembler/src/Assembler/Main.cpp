#include "Assembler/CLI.h"
#include "Assembler/Assembler.h"
#include "Assembler/Output.h"

#include <iostream>

int main(int argc, char** argv)
{
	if (argc == 1) {
		std::cout << "Usage: Assembler [options] file.asm\n\n";
		std::cout << "Type 'Assembler -h' for help.\n";
		return 1;
	}

	Arguments args = parseArguments(argc, argv);

	if (args.Flags.contains("-h")) {
		cli_printHelp();
		return 0;
	}
	
	std::filesystem::path srcPath = args.List[args.List.size() - 1];
	
	Assembler assembler(srcPath);

	if (!assembler.Success()) {
		return 2;
	}

	const std::vector<AssemblyLine>& asmLines = assembler.GetOutput();;

	OutputFormat outputFormat = getOutputFormat(args);
	std::filesystem::path outPath = getOutputPath(args, srcPath, outputFormat);
	writeToFile(outPath, asmLines, outputFormat);
	
	return 0;
}
