#pragma once

#include "Mystery.h"

// Class to represent bogus spaces.
class Bogus : public Mystery
{
protected:
	void Spin(PlayerSharedPtr) override;
public:
	Bogus(const std::string&, std::weak_ptr<Spinner>);
	virtual void Lands(PlayerSharedPtr) override;
};

