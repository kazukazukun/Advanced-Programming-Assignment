#ifndef CSPACE
#define CSPACE

#include "CPlayer.h"
#include <memory>

class CPlayer;
// Defines a type alias for a CPlayer type shared pointer.
typedef std::shared_ptr<CPlayer> PlayerSharedPtr;

class CSpace
{
protected:
	// Holds space name.
	std::string mName = "";
public:
	virtual ~CSpace() {};
	CSpace(const std::string&);
	virtual void Lands(PlayerSharedPtr) = 0;
};

#endif