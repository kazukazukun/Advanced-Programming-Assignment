#include "PlagiarismHearing.h"

PlagiarismHearing::PlagiarismHearing(const std::string& kName) : Effective(kName) {};

void PlagiarismHearing::Lands(PlayerSharedPtr pPlayer)
{
	if (pPlayer->IsPlagiarized())
	{
		pPlayer->UnflagPlagiarized();
		pPlayer->DecrementMotivationBy(mMotivationLoss);
		std::cout << " and goes to the Hearing\n";
		std::cout << pPlayer->GetName() << " loses motivation\n";
	}
	else
	{
		std::cout << pPlayer->GetName() << " lands on Plagiarism Hearing\n";
		std::cout << " and supports their friend\n";
	}
}