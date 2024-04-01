#include "Assessment.h"

/**
 * @brief Creates an assessment object with the provided params.
 * @param[in] kName, Name of the space.
 * @param[in] kMotivation, Motivation cost.
 * @param[in] kSuccess, Gainable success.
 */
Assessment::Assessment(const std::string& kName, const unsigned short& kMotivation,
	const unsigned short& kSuccess, const unsigned short& kYear) : Activity(kName, kMotivation, kSuccess)
{
	mYear = kYear;
}

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
unsigned short Assessment::DeferMotivationValue() const
{
	return mMotivationCost;
}

/**
 * @brief Retrieves the sacrificable success when deferring the assessment.
 * @return mSuccess, the original success.
 */
unsigned short Assessment::DeferSuccessValue() const
{
	return mSuccess;
}

/**
 * @brief Landed player gets help from other completers.
 * 
 * All the completers help the landed player and gain success.
 */
void Assessment::GetHelp(const std::string& kHelpReciever)
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

void Assessment::Lands(PlayerSharedPtr pPlayer)
{
	std::cout << pPlayer->GetName() << " lands on " << mName << '\n';
	if (pPlayer->HasCompleted(shared_from_this()))
	{
		std::cout << pPlayer->GetName() << " has already completed the " << mName << '\n';
		return;

	}
	if (GetMotivationCost() <= pPlayer->GetMotivation())
	{
		pPlayer->CompleteActivity(shared_from_this());
		AddCompleter(pPlayer);
	}
	else
	{
		std::cout << pPlayer->GetName() << " doesn't have the " << GetMotivationCost();
		std::cout << " motivation to complete the " << mName << '\n';
	}
}