#include "MysteryData.h"

/**
 * @brief Creates an instance of the class with provided data.
 * @param[in] kMotivation, The motivation.
 * @param[in] kIncident, The incident.
 */
MysteryData::MysteryData(const unsigned short& kMotivation, const std::string& kIncident)
{
	mMotivation = kMotivation;
	mIncident = kIncident;
}

/**
 * @brief Retrieves motivation.
 * @return mMotivation.
 */
unsigned short MysteryData::GetMotivation() const
{
	return mMotivation;
}

/**
 * @brief Retrieves the incident.
 * @return mIncident.
 */
std::string MysteryData::GetIncident() const
{
	return mIncident;
}