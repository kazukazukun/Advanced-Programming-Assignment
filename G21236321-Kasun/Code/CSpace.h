#pragma once

#include "CPlayer.h"
#include <memory>

class CPlayer;
// Defines a type alias for a CPlayer type shared pointer.
typedef std::shared_ptr<CPlayer> PlayerSharedPtr;

// Represents a space on the board.
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

// Defines a type alias for a vector of CSpace type shared pointers.
typedef std::vector<std::shared_ptr<CSpace>> Spaces;