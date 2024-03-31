#ifndef CSPACE
#define CSPACE

#include "CPlayer.h"

class CSpace
{
protected:
	std::string mName = "";
public:
	virtual ~CSpace() = 0;
	virtual void Lands(CPlayer*) = 0;
};

#endif