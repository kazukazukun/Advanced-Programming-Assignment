#include "DataReading.h"
#include <fstream>
#include <string>
#include <vector>

// Defines a type alias for a vector of strings.
typedef std::vector<std::string> Strings;

/**
 * @brief Opens a file with the provided file name.
 *
 * @param[in] kFileName, File name of the file to open.
 * @return file, return An opened file if it was successfully opened,
 * otherwise a default-constructed std::ifstream object indicating failure.
 */
std::ifstream DataReading::OpenFile(const std::string& kFileName)
{
	try
	{
		std::ifstream file(mRelativePath + kFileName);
		if (!file.is_open())
		{
			throw std::runtime_error("Failed to open file for reading");
		}
		return file;
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Error: " << exception.what() << std::endl;
		return std::ifstream();
	}

}

/**
 * @brief Reads an int from the provided text file name.
 *
 * Opens the file with the provided file name, reads the first line of the file,
 * converts it to an int, and returns the result.
 * @param[in] kFileName, File name of the file containing the seed.
 * @return seed, The integer seed read from the file.
 * Returns 0 if the file cannot be opened or if the file is empty.
 */
int DataReading::GetSeed(const std::string& kFileName)
{
	int seed = 0;
	std::ifstream file = OpenFile(kFileName);
	if (file.is_open())
	{
		std::string line = "";
		std::getline(file, line);
		seed = std::stoi(line);
		file.close();
	}
	return seed;
}

/**
 * @brief Reads details of CSpaces from a text file.
 *
 * Opens the file by provided file name, reads its content line by line,
 * and stores each line of CSpace details as a separate element in a vector of strings.
 *
 * @param[in] kFileName, File name of the text file containing details of CSpaces.
 * @return Spaces, A vector of strings containing the details of CSpaces read from the file,
 *         with each line's details stored as a separate string.
 *         If the file cannot be opened or is empty, an empty vector is returned.
 */
Strings DataReading::GetCSpaces(const std::string& kFileName)
{
	Strings Spaces;
	std::ifstream file = OpenFile(kFileName);
	if (file.is_open())
	{
		std::string line = "";
		while (std::getline(file, line))
		{
			Spaces.push_back(line);
		}
		file.close();
	}
	return Spaces;
}