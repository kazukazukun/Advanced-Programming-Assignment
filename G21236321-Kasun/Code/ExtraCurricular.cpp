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
 * @brief Landed player motivates completers.
 *
 * Landed player motivates the completers by joining their activity.
 * The completers' success is incremented as well.
 */
void ExtraCurricular::GetHelp(const std::string& kMotivator)
{
	if (!mCompleters.empty())
	{
		for (auto completer = mCompleters.begin(); completer != mCompleters.end(); ++completer)
		{
			if (auto pCompleter = completer->lock())
			{
				pCompleter->SupportFriend(GetSuccess(), GetMotivationCost(), kMotivator);
			}
		}
	}
}

/**
 * @brief Land method.
 * 
 * When a player lands, an appropriate message is printed.
 * If the player has already completed the activity, an appropriate
 * message is printed based on the activity type.
 * If the player has not completed the activity and has enough
 * motivation to do so, completes the activity and adds player to completers
 * Otherwise, an appropriate message is printed stating the low motication of the player.
 * 
 * @param[in] pPlayer, The landed player.
 */
void ExtraCurricular::Lands(PlayerSharedPtr pPlayer)
{
	std::cout << pPlayer->GetName() << " lands on " << mName << '\n';
	if (pPlayer->HasCompleted(shared_from_this()))
	{
		std::cout << pPlayer->GetName() << " has already undertaken the activity " << mName << '\n';
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