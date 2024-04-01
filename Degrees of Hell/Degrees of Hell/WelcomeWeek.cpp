#include "WelcomeWeek.h"

WelcomeWeek::WelcomeWeek(const std::string& kName) : Ineffective(kName) {};

void WelcomeWeek::Lands(PlayerSharedPtr pPlayer)
{
	std::cout << pPlayer->GetName() << " lands on " << mName << '\n';
}