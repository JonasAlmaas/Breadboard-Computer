#include "Assembler/Arguments.h"

#include <iostream>

Arguments parseArguments(int argc, char** argv)
{
	Arguments args;

	char* value = nullptr;
	for (int i = 0; i < argc; ++i) {
		value = argv[i];

		args.List.push_back(std::string(value));

		if (strcmp(value, "-o") == 0 ||
			strcmp(value, "-f") == 0) {

			if (i + 1 >= argc) {
				std::cout << "Missing value for argument '" << value << "'" << std::endl;
				break;
			}

			args.Table[value] = std::string(argv[i + 1]);
			++i;
		}
	}

	return args;
}
