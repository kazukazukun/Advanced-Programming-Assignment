#pragma once

#include "Activity.h"

// Represents an extra-curricular space.
class ExtraCurricular : public Activity
{
public:
	ExtraCurricular(const std::string&, const unsigned short&, const unsigned short&);

	void GetHelp(const std::string&) override;
	virtual void Lands(PlayerSharedPtr) override;
};
