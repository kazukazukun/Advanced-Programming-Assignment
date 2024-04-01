#pragma once

#include "Activity.h"
#include <memory>

// Class to represent assessments spaces in the game.
class Assessment : public Activity
{
private:
	// Holds the year of the assessment.
	unsigned short mYear = 0;
public:
	Assessment(const std::string&, const unsigned short&, const unsigned short&, const unsigned short&);

	unsigned short GetYear() const;
	unsigned short DeferMotivationValue() const;
	unsigned short DeferSuccessValue() const;
	void RemoveCompleter(PlayerSharedPtr);
	void GetHelp(const std::string&) override;
	virtual void Lands(PlayerSharedPtr) override;
};

// Defines a type alias for a Assessment type shared pointer.
typedef std::shared_ptr<Assessment> AssessmentSharedPtr;
// Defines a type alias for a vector of Assessment type shared pointers.
typedef std::vector<AssessmentSharedPtr> Assessments;

