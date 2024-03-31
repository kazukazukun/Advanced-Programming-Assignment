#ifndef BONUS
#define BONUS

#include "Mystery.h"

class Bonus : public Mystery
{
protected:
	void Spin(PlayerSharedPtr) override;
public:
	Bonus(const std::string&);
	virtual void Lands(PlayerSharedPtr) override;
};

#endif