#pragma once

#include "CSpace.h"

class Event : public CSpace
{
public:
	virtual ~Event() {};
	Event(const std::string&);
	virtual void Lands(PlayerSharedPtr) = 0;
};
