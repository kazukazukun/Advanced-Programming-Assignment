#include "CPlayer.h"
#include "Activity.h"
#include "Assessment.h"
#include <typeinfo>

/**
 * @brief Constructs a new CPlayer object with the provided name.
 * 
 * Initializes the player with the specified name,
 * setting default values for other attributes.
 * 
 * @param[in] kName, The name of the player.
 */
CPlayer::CPlayer(const std::string& kName)
{
	mName = kName;
	mYear = 1;
	mMotivation = 1000;
	mSuccess = 0;
	mPosition = 0;
}

/**
 * @brief Retrieves the current position of the player.
 * @return mPosition, The current position of the player.
 */
unsigned short CPlayer::GetPosition() const
{
	return mPosition;
}

/**
 * @brief Retrieves the current study year.
 * @return mYear, The current study year of the player.
 */
unsigned short CPlayer::GetYear() const
{
	return mYear;
}

/**
 * @brief Increments study year by 1.
 */
void CPlayer::IncrementYear()
{
	mYear++;
}

/**
 * @brief Checks whether the player has been accused of plagiarism.
 * @return mPlagiarized, true if the player has been accused of plagiarism, false otherwise.
 */
bool CPlayer::IsPlagiarized() const
{
	return mPlagiarized;
}

/**
 * @brief Flags plagiarized.
 */
void CPlayer::FlagPlagiarized()
{
	mPlagiarized = true;
}

/**
 * @brief Un-Flags plagiarized.
 */
void CPlayer::UnflagPlagiarized()
{
	mPlagiarized = false;
}

/**
 * @brief Increments the player success by the provided amount.
 * @param[in] kAmount, The amount to be incremented.
 */
void CPlayer::IncrementSuccessBy(const unsigned int& kAmount)
{
	mSuccess += kAmount;
}

/**
 * @brief Decrements the player success by the provided amount.
 * @param[in] kAmount, The amount to be decremented. 
 */
void CPlayer::DecrementSuccessBy(const unsigned int& kAmount)
{
	mSuccess -= kAmount;
}

void CPlayer::RegainMotivation()
{
	while (!IsMotivated() && !mPortfolio.empty())
	{
		Assessments lowMotivationAssessments;
		for (auto assessment = mPortfolio.begin(); assessment != mPortfolio.end(); ++assessment)
		{
			if (auto pDeferringAssessment = std::dynamic_pointer_cast<Assessment>(assessment->lock()))
			{
				if (lowMotivationAssessments.empty())
				{
					lowMotivationAssessments.push_back(pDeferringAssessment);
					continue;
				}
				if (lowMotivationAssessments.front()->RegainableMotivation() == pDeferringAssessment->SacrificableSuccess())
				{
					lowMotivationAssessments.push_back(pDeferringAssessment);
				}
				else if(lowMotivationAssessments.front()->RegainableMotivation() > pDeferringAssessment->SacrificableSuccess())
				{
					lowMotivationAssessments.clear();
					lowMotivationAssessments.push_back(pDeferringAssessment);
				}
			}
		}
		if (lowMotivationAssessments.size() == 1)
		{
			DeferAssessment(lowMotivationAssessments.front());
			continue;
		}
		switch (mYear)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
void CPlayer::DeferAssessment(ActivitySharedPtr pActivity)
{
	for (auto assessment = mPortfolio.begin(); assessment != mPortfolio.end(); ++assessment)
	{
		if (auto pAssessment = assessment->lock())
		{
			if (pActivity == pAssessment)
			{
				if (auto pDeferringAssessment = std::dynamic_pointer_cast<Assessment>(pActivity))
				{
					mPortfolio.erase(assessment);
					mDeferredPortfolio.push_back(pActivity);
					IncrementMotivationBy(pDeferringAssessment->RegainableMotivation());
					DecrementSuccessBy(pDeferringAssessment->SacrificableSuccess());
					// Remove player from completers in assessments
					// Do a print here
					break;
				}
			}
		}
	}
}

/**
 * @brief Sets provided name as player name.
 * @param[in] kName, The name. 
 */
void CPlayer::SetName(const std::string& kName)
{
	mName = kName;
}

/**
 * @brief Retrieves the player name. 
 * @return mName, The player name.
 */
std::string CPlayer::GetName() const
{
	return mName;
}

/**
 * @brief Retrieves the player motivation.
 * @return mMotivation, The current motivation.
 */
int CPlayer::GetMotivation() const
{
	return mMotivation;
}

/**
 * @brief Increments the player motivation by the provided amount.
 * @param[in] kAmount, The amount to be incremented.
 */
void CPlayer::IncrementMotivationBy(const unsigned int& kAmount)
{
	mMotivation += kAmount;
}

/**
 * @brief Decrements the player motivation by the provided amount.
 * @param[in] kAmount, The amount to be decremented.
 */
void CPlayer::DecrementMotivationBy(const unsigned int& kAmount)
{
	mMotivation -= kAmount;
}

/**
 * @brief Sets player position to the provided position.
 * @param[in] kPosition, The provided position.
 */
void CPlayer::SetPosition(const unsigned short& kPosition)
{
	mPosition = kPosition;
}

/**
 * @brief Adds the provided activity to mPortfolio.
 * @param pActivity[in], The weak ptr of the activity.
 */
void CPlayer::AddToPortfolio(ActivityWeakPtr pActivity)
{
	mPortfolio.push_back(pActivity);
}

/**
 * @brief Completes provided activity.
 * 
 * Deducts motivation cost for the activity from the player.
 * Adds up success gain for the activity to the player.
 * Gets help with activity completion from completers, if there're any.
 * If the provided activity is of type assessment, it is added to mPortfolio.
 * Otherwise, it is added to mAccomplishments.
 * @param pActivity[in], The shared ptr of the activity to be completed.
 */
void CPlayer::CompleteActivity(ActivitySharedPtr pActivity)
{
	DecrementMotivationBy(pActivity->GetMotivationCost());
	IncrementSuccessBy(pActivity->GetSuccess());
	pActivity->GetHelp();
	if (typeid(*pActivity) == typeid(Assessment))
	{
		AddToPortfolio(pActivity);
	}
	else
	{
		AddToAccomplishments(pActivity);
	}
}

/**
 * @brief Supports a player by joining their extra-curricular activity.
 * 
 * Increments motivation and success gained by joining the activity.
 * @param[in] kSuccessGain, success to increment.
 * @param[in] kMotivationGain, motivation to increment. 
 */
void CPlayer::SupportFriend(const unsigned short& kSuccessGain, const unsigned short& kMotivationGain)
{
	// Do a Print here
	mSuccess += kSuccessGain;
	mMotivation += kMotivationGain;
}

/**
 * @brief Supports a player by helping their assessment.
 * 
 * Increments success gained by joining the activity.
 * @param[in] kSuccessGain, success to gain.
 */
void CPlayer::SupportFriend(const unsigned short& kSuccessGain)
{
	// Do a print here
	mSuccess += kSuccessGain;
}

/**
 * @brief Checks if the player has completed the provided activity.
 *
 * This method checks if the player has completed the activity indicated by the
 * shared pointer to the activity object provided as the argument.
 * If the provided activity is of type Assessment, it searches through the player's
 * portfolio of completed assessments. Otherwise, it searches through the player's
 * list of accomplishments.
 *
 * @param[in] pActivity, A shared pointer to the activity to be checked for completion.
 * @return true if the player has completed the provided activity, false otherwise.
 */
bool CPlayer::HasCompleted(ActivitySharedPtr pActivity)
{
	if (typeid(*pActivity) == typeid(Assessment))
	{
		// Search through the player's portfolio of completed assessments.
		for (auto assessment = mPortfolio.begin(); assessment != mPortfolio.end(); ++assessment)
		{
			if (auto pAssessment = assessment->lock())
			{
				if (pActivity == pAssessment)
				{
					return true;
				}
			}
		}
	}
	else
	{
		// Search through the player's list of completed accomplishments.
		for (auto accomplishment = mAccomplishments.begin(); accomplishment != mAccomplishments.end(); ++accomplishment)
		{
			if (auto pAccomplishment = accomplishment->lock())
			{
				if (pActivity == pAccomplishment)
				{
					return true;
				}
			}
		}
	}
	return false;
}

/**
 * @brief Adds an Extra-Curricular activity to the player's list of accomplishments.
 *
 * @param[in] pActivity, A weak pointer to the Extra-Curricular activity to be added to the list of accomplishments.
 */
void CPlayer::AddToAccomplishments(ActivityWeakPtr pActivity)
{
	mAccomplishments.push_back(pActivity);
}

/**
 * @brief Checks if the player can advance to the next year based on their number of completed assessments.
 *
 * This method checks if the player has completed at least the specified minimum number of assessments for the current year.
 *
 * @param[in] minNumOfAssessments, The minimum number of assessments required to advance to the next year (default: 3).
 * @return true if the player can advance to the next year based on the minimum number of assessments completed, false otherwise.
 */
bool CPlayer::CanAdvance(unsigned short minNumOfAssessments = 3)
{
	unsigned short numOfAssessments = 0;
	for (auto assessment = mPortfolio.begin(); assessment != mPortfolio.end(); ++assessment)
	{
		if (auto pAssessment = std::dynamic_pointer_cast<Assessment>(assessment->lock()))
		{
			if (pAssessment->GetYear() == GetYear())
			{
				numOfAssessments++;
			}
		}
	}
	return numOfAssessments >= minNumOfAssessments;
}

/**
 * @brief Checks if the player is motivated.
 * @return True if motivation is greater than or equal to zero. Otherwise, false.
 */
bool CPlayer::IsMotivated() const
{
	return mMotivation >= 0;
}