#include "AccusedOfPlagiarism.h"

/**
 * @brief Constructor.
 * @param[in] kName, The name of the space.
 */
AccusedOfPlagiarism::AccusedOfPlagiarism(const std::string& kName) : Effective(kName) {};

/**
 * @brief Land method.
 * 
 * Prints about player landing.
 * Flags them plagiarized.
 * Moves them to Plagiarism Hearing space.
 * 
 * @param[in] pPlayer, The landed player.
 */
void AccusedOfPlagiarism::Lands(PlayerSharedPtr pPlayer)
{
	std::cout << pPlayer->GetName() << " lands on " << mName << '\n';
	pPlayer->FlagPlagiarized();
	pPlayer->SetPosition(mHearingSpaceIndex);
	mpHearingSpace.lock()->Lands(pPlayer);
}

/**
 * @brief Sets Plagiarism hearing space's index and weak ptr.
 * @param[in] kIndex, The index of the Plagiarism hearing space.
 * @param[in] pSpace, The weak ptr of the Plagiarism hearing space.
 */
void AccusedOfPlagiarism::SetHearingSpace(const short& kIndex, std::weak_ptr<PlagiarismHearing> pSpace)
{
	mHearingSpaceIndex = kIndex;
	mpHearingSpace = pSpace;
}