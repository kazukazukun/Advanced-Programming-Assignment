#ifndef ACTIVITY
#define ACTIVITY

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
typedef std::vector<PlayerWeakPtr> Players;

class Activity : public CSpace
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
	Players mCompleters;
public:
	virtual ~Activity() {};
	Activity(const std::string&);

	virtual void GetHelp() = 0;
	void AddCompleter(PlayerWeakPtr);
	unsigned short GetMotivationCost();
	unsigned short GetSuccess();
	virtual void Lands(PlayerSharedPtr) = 0;
};

#endif