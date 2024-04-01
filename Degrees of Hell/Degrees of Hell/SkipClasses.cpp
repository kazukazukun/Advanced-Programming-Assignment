#include "SkipClasses.h"

SkipClasses::SkipClasses(const std::string& kName) : Ineffective(kName) {};

void SkipClasses::Lands(PlayerSharedPtr pPlayer)
{
	std::cout << pPlayer->GetName() << " lands on " << mName << '\n';
	std::cout << " and hangs out with their dodgy mates\n";
}