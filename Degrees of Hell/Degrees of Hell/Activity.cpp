#include "Activity.h"
#include <cmath>

/**
 * @brief Constructor.
 * @param[in] kName, Name of the space.
 * @param[in] kMotivation, Motivation cost.
 * @param[in] kSuccess, Gainable success.
 */
Activity::Activity(const std::string& kName, const unsigned short& kMotivation,
	const unsigned short& kSuccess) : CSpace(kName)
{
	mMotivationCost = kMotivation;
	mSuccess = kSuccess;
}

/**
 * @brief Retrieves task name.
 * @return mName.
 */
std::string Activity::GetName()
{
	return mName;
}

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

/**
 * @brief Removes provided player from mCompleters.
 * @param[in] pPlayer, The player to be removed.
 */
void Activity::RemoveCompleter(PlayerSharedPtr pPlayer)
{
	for (auto player = mCompleters.begin(); player != mCompleters.end(); ++player)
	{
		if (auto pCompleter = player->lock())
		{
			if (pPlayer == pCompleter)
			{
				mCompleters.erase(player);
				break;
			}
		}
	}
}
