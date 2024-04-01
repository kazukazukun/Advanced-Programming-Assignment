#pragma once

#include "Activity.h"
class ExtraCurricular : public Activity
{
public:
	ExtraCurricular(const std::string&, const unsigned short&, const unsigned short&);

	void GetHelp() override;
	virtual void Lands(PlayerSharedPtr) override;
};
