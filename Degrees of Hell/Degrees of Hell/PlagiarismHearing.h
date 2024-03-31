#ifndef PLAGIARISMHEARING
#define PLAGIARISMHEARING

#include "Effective.h"

class PlagiarismHearing : public Effective
{
public:
	virtual void Lands(PlayerSharedPtr) override;
};

#endif