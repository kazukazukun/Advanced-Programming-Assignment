#ifndef MYSTERYDATA
#define MYSTERYDATA

#include <iostream>
#include <vector>

// A class to hold data for bonus and bogus.
class MysteryData
{
private:
	// Holds motivation.
	unsigned short mMotivation = 0;
	// Holds the incident.
	std::string mIncident = "";
public:
	MysteryData(const unsigned short&, const std::string&);

	unsigned short GetMotivation() const;
	std::string GetIncident() const;
};

// Defines a type alias for a vector of MysteryData objects.
typedef std::vector<MysteryData> Mysteries;

#endif