#pragma once

#include "Mystery.h"

class Bonus : public Mystery
{
protected:
	void Spin(PlayerSharedPtr) override;
public:
	Bonus(const std::string&, std::weak_ptr<Spinner>);
	virtual void Lands(PlayerSharedPtr) override;
};

