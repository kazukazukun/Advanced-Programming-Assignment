#include "Assessment.h"

/**
 * @brief Retrieves the year of the assessment.
 * @return mYear, the year of the assessment.
 */
unsigned short Assessment::GetYear() const
{
	return mYear;
}

/**
 * @brief Retrieves the gainable motivation by deferring the assessment.
 * @return mOtivationCost, the original motivation cost.
 */
unsigned short Assessment::RegainableMotivation() const
{
	return mMotivationCost;
}

/**
 * @brief Retrieves the sacrificable success when deferring the assessment.
 * @return mSuccess, the original success.
 */
unsigned short Assessment::SacrificableSuccess() const
{
	return mSuccess;
}

/**
 * @brief Landed player gets help from other completers.
 * 
 * All the completers help the landed player and gain success.
 */
void Assessment::GetHelp()
{
	if (!mCompleters.empty())
	{
		for (auto completer = mCompleters.begin(); completer != mCompleters.end(); ++completer)
		{
			if (auto pCompleter = completer->lock())
			{
				pCompleter->SupportFriend(GetSuccess());
			}
		}
	}
}