#ifndef WELCOMEWEEK
#define WELCOMEWEEK

#include "Ineffective.h"

class WelcomeWeek : public Ineffective
{
public:
	virtual void Lands(PlayerSharedPtr) override;
};

#endif