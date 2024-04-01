#include "AccusedOfPlagiarism.h"

AccusedOfPlagiarism::AccusedOfPlagiarism(const std::string& kName) : Effective(kName) {};

void AccusedOfPlagiarism::Lands(PlayerSharedPtr pPlayer)
{
	std::cout << pPlayer->GetName() << " lands on " << mName << '\n';
	pPlayer->FlagPlagiarized();
	pPlayer->SetPosition(mHearingSpaceIndex);
	mpHearingSpace.lock()->Lands(pPlayer);
}


void AccusedOfPlagiarism::SetHearingSpace(const short& kIndex, std::weak_ptr<PlagiarismHearing> pSpace)
{
	mHearingSpaceIndex = kIndex;
	mpHearingSpace = pSpace;
}