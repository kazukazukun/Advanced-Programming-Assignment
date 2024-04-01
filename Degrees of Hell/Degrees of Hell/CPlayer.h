#pragma once

#include <iostream>
#include <vector>
#include <memory>

class Activity;

// Defines a type alias for a Activity type weak pointer.
typedef std::weak_ptr<Activity> ActivityWeakPtr;
// Defines a type alias for a Activity type shared pointer.
typedef std::shared_ptr<Activity> ActivitySharedPtr;
// Defines a type alias for a vector of Activity type weak pointers.
typedef std::vector<ActivityWeakPtr> Activites;
// Defines a type alias for a vector of unsigned shorts.
typedef std::vector<unsigned short> Shorts;

// Class to represent players in the game.
// Inherits from enable_shared_from_this to pass shared pointer of instances to other functions.
class CPlayer : public std::enable_shared_from_this<CPlayer>
{
private:
	// Holds player name
	std::string mName = "";
	// Holds player motivation
	int mMotivation = 0;
	// Holds player success
	unsigned int mSuccess = 0;
	// Holds player position in the board
	unsigned short mPosition = 0;
	// Holds player year of study
	unsigned short mYear = 0;
	// Flag indicating whether the player has been accused of plagiarism
	bool mPlagiarized = false;
	// Holds completed assessments
	Activites mPortfolio;
	// Holds deferred assessments
	Activites mDeferredPortfolio;
	// Holds completed Extra-curricular activites
	Activites mAccomplishments;

	unsigned short GetPosition() const;
	void SetPosition(unsigned short&);
	void IncrementYear();
	void DecrementSuccessBy(const unsigned int&);
	void DeferAssessment(ActivitySharedPtr);
	void AddToAccomplishments(ActivityWeakPtr);
	void AddToPortfolio(ActivityWeakPtr);
	Shorts Prioritize(const short&, const short);
	void Resubmit(ActivitySharedPtr);
	Activites GetLowMotivationAssessments(const bool);

public:

	CPlayer(const std::string&);

	void SetName(const std::string&);
	std::string GetName() const;
	int GetMotivation() const;
	unsigned short GetYear() const;
	void IncrementMotivationBy(const unsigned int&);
	void DecrementMotivationBy(const unsigned int&);
	void IncrementSuccessBy(const unsigned int&);
	void SetPosition(const unsigned short&);
	bool IsPlagiarized() const;
	void FlagPlagiarized();
	void UnflagPlagiarized();
	bool HasCompleted(ActivitySharedPtr);
	void CompleteActivity(ActivitySharedPtr);
	void RegainMotivation();
	bool IsMotivated() const;
	bool CanAdvance(unsigned short);
	void SupportFriend(const unsigned short&, const unsigned short&);
	void SupportFriend(const unsigned short&);
	void ResubmitAssessments();
};
