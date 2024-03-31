#ifndef SKIPCLASSES
#define SKIPCLASSES

#include "Ineffective.h"

class SkipClasses : public Ineffective
{
public:
	virtual void Lands(PlayerSharedPtr) override;
};

#endif