#pragma once

#include "Ineffective.h"

class SkipClasses : public Ineffective
{
public:
	SkipClasses(const std::string&);
	virtual void Lands(PlayerSharedPtr) override;
};
