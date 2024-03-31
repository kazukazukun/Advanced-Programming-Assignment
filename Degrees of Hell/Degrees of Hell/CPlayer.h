#ifndef CPLAYER
#define CPLAYER

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

// Class to represent players in the game.
class CPlayer
{
private:

	/**
	 * @brief Struct to hold priority orders for deferring assessments.
	 * 
	 * This struct is used to store priority orders for deferring assessments.
	 * When deferring an assessment and if there are two or more assessments
	 * with the same motivational cost, the assessment that gets deferred
	 * differs based on the priority order defined here.
	 * 
	 * The struct contains priority year orders of assessments in descending order for each player year.
	 */
	struct PriorityOrders
	{
	public:
		// Priority order for the first year: Highest priority assessment is deferred last.
		short mFirstYear[3] = {3, 2, 1};
		// Priority order for the second year: Highest priority assessment is deferred last.
		short mSecondYear[3] = {1, 3, 2};
		// Priority order for the third year: Highest priority assessment is deferred last.
		short mThirdYear[3] = {2, 1, 3};
	};

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
	bool IsPlagiarized() const;
	void FlagPlagiarized();
	void UnflagPlagiarized();
	void DecrementSuccessBy(const unsigned int&);
	void DeferAssessment(ActivitySharedPtr);
	void AddToAccomplishments(ActivityWeakPtr);
	void AddToPortfolio(ActivityWeakPtr);

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
	bool HasCompleted(ActivitySharedPtr);
	void CompleteActivity(ActivitySharedPtr);
	void RegainMotivation();
	bool IsMotivated() const;
	bool CanAdvance(unsigned short);
	void SupportFriend(const unsigned short&, const unsigned short&);
	void SupportFriend(const unsigned short&);
};

#endif