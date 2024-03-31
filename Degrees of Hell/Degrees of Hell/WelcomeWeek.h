#pragma once

#include "Ineffective.h"

class WelcomeWeek : public Ineffective
{
public:
	virtual void Lands(PlayerSharedPtr) override;
};
