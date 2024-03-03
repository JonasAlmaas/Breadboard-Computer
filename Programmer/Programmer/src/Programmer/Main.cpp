#include "Programmer/Arguments.h"
#include "Programmer/CLI.h"
#include "Programmer/SerialPort.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>

namespace Utils {

	static std::string binaryString(uint32_t value, uint8_t bitCount = 8, uint8_t tickOffset = 0)
	{
		char result[256]{};
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

int readInProgram(const std::filesystem::path &filePath, char *buffer, size_t bufferSize)
{
	std::ifstream file(filePath, std::ios::in | std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		return -1;
	}
	
	file.read((char*)buffer, bufferSize);

	if (file.gcount() == bufferSize && !file.eof()) {
		std::cerr << "Error: Max program size if 256 bytes" << std::endl;
		return -1;
	}

	file.close();

	return file.gcount();
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		cli_printHelp();
		return 1;
	}

	Arguments args = parseArguments(argc, argv);

	if (args.Flags.contains("-h") || !args.Flags.contains("-p")) {
		cli_printHelp();
		return 0;
	}
	
	SerialPort sp(args.Table.at("-p"));

	std::filesystem::path filePath = args.List[args.List.size() - 1];

	unsigned char buffer[256];
	int bytesRead = readInProgram(filePath, (char*)&buffer, 256);

	if (bytesRead == -1) {
		return 1;
	}

	char programData[15];
	char responseBuffer[256];

	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	for (int i = 0; i < bytesRead; i++) {
		std::cout << Utils::binaryString(i, 8, 4) << " <- " << Utils::binaryString(buffer[i], 8, 4);
		sprintf(programData, "0x%02x:0x%02x\n", i, buffer[i]);
		std::cout << " - " << programData;

		sp.Write(programData, 10);
		
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		//memset(responseBuffer, 0, 256);
		//if (!sp.ReadLine(responseBuffer, 256)) {
		//	std::cerr << "Error: Unable to read from serial port" << std::endl;
		//	return 1;
		//}

		//std::cout << responseBuffer << std::endl;
	}
	
	return 0;
}
