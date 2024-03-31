#include "Bogus.h"

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

void Bogus::Spin(PlayerSharedPtr)
{

}

void Bogus::Lands(PlayerSharedPtr pPlayer)
{

}