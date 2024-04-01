#include "WelcomeWeek.h"

WelcomeWeek::WelcomeWeek(const std::string& kName) : Ineffective(kName) {};

/**
 * @brief Land method.
 * 
 * Prints an appropriate message stating the landing.
 * 
 * @param[in] pPlayer, The landed player.
 */
void WelcomeWeek::Lands(PlayerSharedPtr pPlayer)
{
	std::cout << pPlayer->GetName() << " lands on " << mName << '\n';
}