#ifndef INEFFECTIVE
#define INEFFECTIVE

#include "Event.h"

class Ineffective : public Event
{
public:
	virtual ~Ineffective() {};
	virtual void Lands(PlayerSharedPtr) = 0;
};

#endif