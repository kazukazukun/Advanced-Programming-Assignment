#include "ExtraCurricular.h"

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