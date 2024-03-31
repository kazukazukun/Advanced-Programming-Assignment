#pragma once

#include <iostream>
#include <vector>

// Defines a type alias for a vector of strings.
typedef std::vector<std::string> Strings;

// Class to handle data reading for the game.
class DataReading
{
private:
	// Stores the relative path for input files.
	const std::string mRelativePath = "Resources/";
	std::ifstream OpenFile(const std::string&);
public:
	int GetSeed(const std::string&);
	Strings GetCSpaces(const std::string&);
};
