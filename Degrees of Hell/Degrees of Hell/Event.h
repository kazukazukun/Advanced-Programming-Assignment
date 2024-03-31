#ifndef EVENT
#define EVENT

#include "CSpace.h"

class Event : public CSpace
{
public:
	virtual ~Event() {};
	virtual void Lands(PlayerSharedPtr) = 0;
};

#endif EVENT