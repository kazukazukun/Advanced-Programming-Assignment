#ifndef MYSTERY
#define MYSTERY

#include "CSpace.h"
#include "MysteryData.h"
#include "Spinner.h"

// A class to store mysteries.
class Mystery : public CSpace
{
protected:
	// Holds a weak ptr to the spinner in degrees.
	std::weak_ptr<Spinner> mpSpinner;
	// Holds the mysteries.
	Mysteries mMysteries;
	virtual void Spin(PlayerSharedPtr) = 0;
public:
	virtual ~Mystery() {};
	Mystery(const std::string&);
	virtual void Lands(PlayerSharedPtr) = 0;
};

#endif