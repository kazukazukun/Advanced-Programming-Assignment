#pragma once

#include "CSpace.h"
#include "CPlayer.h"
#include <vector>
#include <memory>

class CPlayer;

// Defines a type alias for a CPlayer type weak pointer.
typedef std::weak_ptr<CPlayer> PlayerWeakPtr;
// Defines a type alias for a CPlayer type shared pointer.
typedef std::shared_ptr<CPlayer> PlayerSharedPtr;
// Defines a type alias for a vector of CPlayer type weak pointers.
typedef std::vector<PlayerWeakPtr> PlayersWeak;

class Activity : public CSpace, public std::enable_shared_from_this<Activity>
{
private:
	// Holds name of the task.
	std::string mTaskName = "";
protected:
	// Holds the success gained by completing the activity.
	unsigned short mSuccess = 0;
	// Holds the motivation cost it takes to complete the activity.
	unsigned short mMotivationCost = 0;
	// Holds players who completed the activity.
	PlayersWeak mCompleters;
public:
	virtual ~Activity() {};
	Activity(const std::string&, const unsigned short&, const unsigned short&);

	virtual void GetHelp(const std::string&) = 0;
	void AddCompleter(PlayerWeakPtr);
	unsigned short GetMotivationCost();
	unsigned short GetSuccess();
	virtual void Lands(PlayerSharedPtr) = 0;
	std::string GetName();
	void RemoveCompleter(PlayerSharedPtr);
};
