#pragma once

#include "Effective.h"
#include <memory>
#include "PlagiarismHearing.h"

class AccusedOfPlagiarism : public Effective
{
private:
	std::weak_ptr<PlagiarismHearing> mpHearingSpace;
	short mHearingSpaceIndex = 0;
public:
	AccusedOfPlagiarism(const std::string&);
	virtual void Lands(PlayerSharedPtr) override;
	void SetHearingSpace(const short&, std::weak_ptr<PlagiarismHearing>);
};

