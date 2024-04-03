#include "Bonus.h"

/**
 * @brief Constructor.
 *
 * Assigns provided name as space name,
 * sets the provided weak ptr of the spinner created on the Degrees class to the mpSpinner.
 * Populates mMysteries.
 *
 * @param[in] kName, The name of the space.
 * @param[in] pSpinner, The spinner weak ptr.
 */
Bonus::Bonus(const std::string& kName, std::weak_ptr<Spinner> pSpinner) : Mystery(kName, pSpinner)
{
	mMysteries.push_back(MysteryData(20, "Receive some useful feedback."));
	mMysteries.push_back(MysteryData(50, "Win a hackathon."));
	mMysteries.push_back(MysteryData(80, "Get a free coffee with full loyalty card."));
	mMysteries.push_back(MysteryData(100, "Impress your lecturer in class."));
	mMysteries.push_back(MysteryData(5, "Motivational talk from course leader"));
	mMysteries.push_back(MysteryData(150, "Secure an industry placement"));
	mMysteries.push_back(MysteryData(200, "Attend an inspiring C++ lecture."));
	mMysteries.push_back(MysteryData(300, "Get your best ever assignment mark"));
	mMysteries.push_back(MysteryData(150, "Make a new romantic friend"));
	mMysteries.push_back(MysteryData(10, "Get elected School President"));
}

/**
 * @brief Spins the spinner and based on the number,
 * plsyer gets a bonus.
 * An appropriate message will be printed.
 * @param[in] pPlayer, The player who spins.
 */
void Bonus::Spin(PlayerSharedPtr pPlayer)
{
	const auto& rolledData = mMysteries[mpSpinner.lock()->Spin(pPlayer->GetName()) - 1];
	pPlayer->IncrementMotivationBy(rolledData.GetMotivation());
	std::cout << rolledData.GetIncident();
	std::cout << " Gain motivation of " << rolledData.GetMotivation() << '\n';
}

/**
 * @brief Land method.
 *
 * An appropriate landing message is printed.
 * Player spins.
 *
 * @param[in] pPlayer, The landed player.
 */
void Bonus::Lands(PlayerSharedPtr pPlayer)
{
	std::cout << pPlayer->GetName() << " lands on " << mName << '\n';
	Spin(pPlayer);

}