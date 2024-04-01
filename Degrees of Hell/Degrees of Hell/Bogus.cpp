#include "Bogus.h"

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
Bogus::Bogus(const std::string& kName, std::weak_ptr<Spinner> pSpinner) : Mystery(kName, pSpinner)
{
	mMysteries.push_back(MysteryData(20, "Fall asleep in a boring lecture."));
	mMysteries.push_back(MysteryData(50, "Meet with coach about poor attendance."));
	mMysteries.push_back(MysteryData(80, "Feel really tired after a night out."));
	mMysteries.push_back(MysteryData(100, "Get kicked out of lab for messing about."));
	mMysteries.push_back(MysteryData(150, "Get dumped before a big night out."));
	mMysteries.push_back(MysteryData(200, "Fail an assignment."));
	mMysteries.push_back(MysteryData(50, "Get caught skipping class."));
	mMysteries.push_back(MysteryData(200, "Your friend drops out of uni."));
	mMysteries.push_back(MysteryData(300, "Nobody turns up to teach your class."));
	mMysteries.push_back(MysteryData(20, "Lecturer changes assignment schedule."));
}

/**
 * @brief Spins the spinner and based on the number,
 * plsyer gets a bogus.
 * An appropriate message will be printed.
 * @param[in] pPlayer, The player who spins.
 */
void Bogus::Spin(PlayerSharedPtr pPlayer)
{
	const auto& rolledData = mMysteries[mpSpinner.lock()->Spin(pPlayer->GetName()) - 1];
	pPlayer->DecrementMotivationBy(rolledData.GetMotivation());
	std::cout << rolledData.GetIncident();
	std::cout << " Lose motivation of " << rolledData.GetMotivation() << '\n';
}

/**
 * @brief Land method.
 * 
 * An appropriate landing message is printed.
 * Player spins.
 * 
 * @param[in] pPlayer, The landed player.
 */
void Bogus::Lands(PlayerSharedPtr pPlayer)
{
	std::cout << pPlayer->GetName() << " lands on " << mName << '\n';
	Spin(pPlayer);
}