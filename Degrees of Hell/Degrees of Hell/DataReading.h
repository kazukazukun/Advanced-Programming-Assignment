#ifndef DATAREADING
#define DATAREADING	

#include <iostream>
#include <vector>

// Defines a type alias for a vector of strings.
typedef std::vector<std::string> Strings;

// Class to handle data reading for the game.
class DataReading
{
private:
	// Stores the relative path for input files
	static const std::string mRelativePath;
	static std::ifstream OpenFile(const std::string&);
public:
	static int GetSeed(const std::string&);
	static Strings GetCSpaces(const std::string&);
};

#endif