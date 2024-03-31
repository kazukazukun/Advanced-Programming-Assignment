#pragma once

#include "Event.h"

class Ineffective : public Event
{
public:
	/*virtual ~Ineffective() {};*/
	virtual void Lands(PlayerSharedPtr) = 0;
};
