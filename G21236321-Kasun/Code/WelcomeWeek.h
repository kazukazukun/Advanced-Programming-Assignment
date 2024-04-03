#pragma once

#include "Ineffective.h"

// Class to represent the welcome week.
class WelcomeWeek : public Ineffective
{
public:
	WelcomeWeek(const std::string&);
	virtual void Lands(PlayerSharedPtr) override;
};
