#ifndef BOGUS
#define BOGUS

#include "Mystery.h"

class Bogus : public Mystery
{
protected:
	void Spin(PlayerSharedPtr) override;
public:
	Bogus(const std::string&);
	virtual void Lands(PlayerSharedPtr) override;
};

#endif