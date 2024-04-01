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
void ExtraCurricular::GetHelp()
{
	if (!mCompleters.empty())
	{
		for (auto completer = mCompleters.begin(); completer != mCompleters.end(); ++completer)
		{
			if (auto pCompleter = completer->lock())
			{
				pCompleter->SupportFriend(GetSuccess(), GetMotivationCost());
			}
		}
	}
}

void ExtraCurricular::Lands(PlayerSharedPtr pPlayer)
{

}