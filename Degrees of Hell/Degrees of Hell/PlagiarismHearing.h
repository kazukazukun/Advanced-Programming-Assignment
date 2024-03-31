#pragma once

#include "Effective.h"

class PlagiarismHearing : public Effective
{
public:
	virtual void Lands(PlayerSharedPtr) override;
};
