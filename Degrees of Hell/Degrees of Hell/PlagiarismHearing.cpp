#include "PlagiarismHearing.h"

PlagiarismHearing::PlagiarismHearing(const std::string& kName) : Effective(kName) {};

void PlagiarismHearing::Lands(PlayerSharedPtr pPlayer)
{
	if (pPlayer->IsPlagiarized())
	{
		pPlayer->UnflagPlagiarized();
		pPlayer->DecrementMotivationBy(mMotivationLoss);
		// Do a print
	}
	else
	{
		// Do a print
	}
}