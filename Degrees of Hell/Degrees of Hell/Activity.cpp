#include "Activity.h"
#include <cmath>

/**
 * @brief Adds the provided player to mCompleters.
 * @param pCompleter[in], The weak ptr of the player.
 */
void Activity::AddCompleter(PlayerWeakPtr pCompleter)
{
	mCompleters.push_back(pCompleter);
}

/**
 * @brief Retrieves motivation cost to perform the activity.
 * 
 * If there are no completers, returns the original motivation cost.
 * Otherwise, casts mMotivationCost into a double to avoid integer division.
 * Divides the mMotivationCost by 2,
 * rounds the value to the nearest whole number and
 * casts the rounded value to an unsigned short.
 * @return The motivation cost for the landed player.
 */
unsigned short Activity::GetMotivationCost()
{
	if (mCompleters.empty())
	{
		return mMotivationCost;
	}
	return static_cast<unsigned short>(round(static_cast<double>(mMotivationCost) / 2));
}

/**
 * @brief Retrieves success gain by performing the activity.
 * 
 * Casts mSuccess into a double to avoid integer division.
 * Divides the mSuccess by the number of completers plus one,
 * representing the player who landed,
 * rounds the value to the nearest whole number and
 * casts the rounded value to an unsigned short.
 * @return The success gain for a single player.
 */
unsigned short Activity::GetSuccess()
{
	return static_cast<unsigned short>(round(static_cast<double>(mSuccess) / (mCompleters.size() + 1)));
}
