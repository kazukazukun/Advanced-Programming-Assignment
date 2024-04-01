#pragma once

#include "Event.h"

class Effective : public Event
{
public:
	virtual ~Effective() {};
	Effective(const std::string&);
	virtual void Lands(PlayerSharedPtr) = 0;
};
