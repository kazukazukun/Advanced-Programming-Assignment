#include "PlagiarismHearing.h"

/**
 * @brief Constructor
 * @param[in] kName, The name of the space.
 */
PlagiarismHearing::PlagiarismHearing(const std::string& kName) : Effective(kName) {};

/**
 * @brief Land method.
 * 
 * Checks if the landed player is plagiarized and if they are,
 * decrements their motivation and print an appropriate message.
 * Otherwise, an appropriate message is printed stating the landing.
 * 
 * @param[in] pPlayer, The landed player.
 */
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