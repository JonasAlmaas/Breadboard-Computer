#pragma once

#include <string>
#include <unordered_map>
#include <set>

struct Arguments
{
	std::vector<std::string> List;
	std::unordered_map<std::string, std::string> Table;
	std::set<std::string> Flags;
};

Arguments parseArguments(int argc, char** argv);
