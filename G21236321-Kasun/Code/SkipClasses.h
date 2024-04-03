#pragma once

#include "Ineffective.h"

// Class to represent Skip Classes spaces.
class SkipClasses : public Ineffective
{
public:
	SkipClasses(const std::string&);
	virtual void Lands(PlayerSharedPtr) override;
};
