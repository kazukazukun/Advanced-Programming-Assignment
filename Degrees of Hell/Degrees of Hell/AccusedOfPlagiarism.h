#pragma once

#include "Effective.h"
#include <memory>
#include "PlagiarismHearing.h"

 // Represent an Accused of plagiarism space.
class AccusedOfPlagiarism : public Effective
{
private:
	// Holds the weak ptr to the Plagiarism Hearing space.
	std::weak_ptr<PlagiarismHearing> mpHearingSpace;
	// Holds the index to the Plagiarism Hearing space.
	short mHearingSpaceIndex = 0;
public:
	AccusedOfPlagiarism(const std::string&);
	virtual void Lands(PlayerSharedPtr) override;
	void SetHearingSpace(const short&, std::weak_ptr<PlagiarismHearing>);
};

