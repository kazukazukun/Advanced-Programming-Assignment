#pragma once

#include "Activity.h"
class ExtraCurricular : public Activity
{
public:
	void GetHelp() override;
	virtual void Lands(PlayerSharedPtr) override;
};
