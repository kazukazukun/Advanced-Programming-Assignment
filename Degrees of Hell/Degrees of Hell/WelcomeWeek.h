#pragma once

#include "Ineffective.h"

class WelcomeWeek : public Ineffective
{
public:
	WelcomeWeek(const std::string&);
	virtual void Lands(PlayerSharedPtr) override;
};
