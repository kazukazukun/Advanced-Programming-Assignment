#pragma once

#include "Event.h"

class Ineffective : public Event
{
public:
	virtual ~Ineffective() {};
	Ineffective(const std::string&);
	virtual void Lands(PlayerSharedPtr) = 0;
};
