#include "Assembler/Arguments.h"

#include <iostream>

Arguments parseArguments(int argc, char** argv)
{
	Arguments args;

	char* value = nullptr;
	for (int i = 0; i < argc; ++i) {
		value = argv[i];

		std::string strValue = std::string(value);

		args.List.push_back(strValue);
		
		if (value[0] == '-' && !args.Flags.contains(strValue)) {
			args.Flags.insert(strValue);
		}

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
