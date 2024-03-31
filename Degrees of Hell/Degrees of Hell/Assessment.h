#ifndef ASSESSMENT
#define ASSESSMENT

#include "Activity.h"

// Class to represent assessments spaces in the game.
class Assessment : public Activity
{
private:
	// Holds the year of the assessment.
	unsigned short mYear = 0;
public:
	unsigned short GetYear() const;
	unsigned short RegainableMotivation() const;
	unsigned short SacrificableSuccess() const;
	void GetHelp() override;
};

// Defines a type alias for a Assessment type shared pointer.
typedef std::shared_ptr<Assessment> AssessmentSharedPtr;
// Defines a type alias for a vector of Assessment type shared pointers.
typedef std::vector<AssessmentSharedPtr> Assessments;

#endif