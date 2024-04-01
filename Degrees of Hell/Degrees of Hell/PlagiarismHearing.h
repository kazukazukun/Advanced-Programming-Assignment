#pragma once

#include "Effective.h"

// Class to represents the Plagiarism Hearing space.
class PlagiarismHearing : public Effective
{
private:
	// Loss of motivation player gets when landed on the space as being plagiarized.
	const unsigned short mMotivationLoss = 50;
public:
	PlagiarismHearing(const std::string&);
	virtual void Lands(PlayerSharedPtr) override;
};
