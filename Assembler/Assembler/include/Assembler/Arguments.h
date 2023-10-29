#pragma once

#include <string>
#include <unordered_map>

struct Arguments
{
	std::vector<std::string> List;
	std::unordered_map<std::string, std::string> Table;
};

Arguments parseArguments(int argc, char** argv);
