#include "ExtraCurricular.h"

/**
 * @brief Creates an ExtraCurricular object with the provided params.
 * 
 * @param[in] kName, Name of the space.
 * @param[in] kMotivation, Motivation cost.
 * @param[in] kSuccess, Gainable sucess, Default: 20.
 */
ExtraCurricular::ExtraCurricular(const std::string& kName,
	const unsigned short& kMotivation, const unsigned short& kSuccess = 20) : Activity(kName, kMotivation, kSuccess) {};

/**
 * @brief Landed player gets help from other completers.
 *
 * All the completers help the landed player and gain success and motivation.
 */
void ExtraCurricular::GetHelp(const std::string& kHelpReciever)
{
	if (!mCompleters.empty())
	{
		for (auto completer = mCompleters.begin(); completer != mCompleters.end(); ++completer)
		{
			if (auto pCompleter = completer->lock())
			{
				pCompleter->SupportFriend(GetSuccess(), GetMotivationCost(), kHelpReciever);
			}
		}
	}
}

/**
 * @brief 
 * @param[in] pPlayer 
 */
void ExtraCurricular::Lands(PlayerSharedPtr pPlayer)
{
	if (pPlayer->HasCompleted(shared_from_this()))
	{
		std::cout << pPlayer->GetName() << " has already undertaken the activity " << mName << '\n';
		return;

	}
	if (GetMotivationCost() <= pPlayer->GetMotivation())
	{
		pPlayer->CompleteActivity(shared_from_this());
	}
	else
	{
		std::cout << pPlayer->GetName() << " doesn't have the " << GetMotivationCost();
		std::cout << " motivation to complete the " << mName << '\n';
	}

}