#ifndef EFFECTIVE
#define EFFECTIVE

#include "Event.h"

class Effective : public Event
{
public:
	virtual ~Effective() {};
	virtual void Lands(PlayerSharedPtr) = 0;
};

#endif EFFECTIVE