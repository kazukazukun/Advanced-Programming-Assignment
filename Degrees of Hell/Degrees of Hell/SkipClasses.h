#pragma once

#include "Ineffective.h"

class SkipClasses : public Ineffective
{
public:
	virtual void Lands(PlayerSharedPtr) override;
};
