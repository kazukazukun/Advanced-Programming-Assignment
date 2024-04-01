#include "CPlayer.h"
#include "Activity.h"
#include "Assessment.h"
#include <typeinfo>
#include <algorithm>

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

/**
 * @brief Prioritizes the assessment years based on the current year and graduation year.
 *
 * This function generates a priority order for assessment years based on the current year (kYear)
 * and the graduation year (kGradYear). It starts from the graduation year and goes back to
 * the current year, wrapping around if necessary.
 *
 * @param[in] kYear, The current year of the player.
 * @param[in] kGradYear, The graduation year of the player. Default value is 3.
 * @return order, A vector of shorts representing the descending priority order of assessment years.
 */
Shorts CPlayer::Prioritize(const short& kYear, const short kGradYear = 3)
{
	Shorts order;
	for (short i = kGradYear; i >= 1; i--)
	{
		short year = kYear + i - 1;
		if (year <= kGradYear)
		{
			order.push_back(year);
		}
		else
		{
			order.push_back(year % kGradYear);
		}
	}
	return order;
}

/**
 * @brief Retrieves the assessments with the lowest motivation cost in a portfolio.
 * 
 * Iterates through either mPortfolio or mDeferredPortfolio and finds the assessments
 * with lowest motivation cost.
 * @param[in] kResubmitting, Iterated through mDeferredPortfolio if true. Otherwise, iterated through mPortfolio.
 * @return lowMotivationAssessments, The list of assessments with the lowest motivation cost.
 */
Activites CPlayer::GetLowMotivationAssessments(const bool kResubmitting = false)
{
	// Holds assessments with the lowest motivation cost.
	Activites lowMotivationAssessments;
	// Selecting the appropriate portfolio based on the value of kResubmitting
	auto& AssessmentList = kResubmitting ? mDeferredPortfolio : mPortfolio;
	// Iterates through the AssessmentList finding the assessment with the lowest motivation cost.
	for (auto assessment = AssessmentList.begin(); assessment != AssessmentList.end(); ++assessment)
	{
		if (auto pDeferringAssessment = std::dynamic_pointer_cast<Assessment>(assessment->lock()))
		{
			// Pushes first assessment to the list, lowMotivationAssessments.
			if (lowMotivationAssessments.empty())
			{
				lowMotivationAssessments.push_back(pDeferringAssessment);
				continue;
			}
			if (auto pLowMotivationAssessment = std::dynamic_pointer_cast<Assessment>(lowMotivationAssessments.front().lock()))
			{
				// Checks if the current lowest motivation cost of the assessments in the list, lowMotivationAssessments,
				// is equal to that of the checking assessment.
				if (pLowMotivationAssessment->DeferMotivationValue() == pDeferringAssessment->DeferMotivationValue())
				{
					// If so, pushes it to the list, lowMotivationAssessments.
					lowMotivationAssessments.push_back(pDeferringAssessment);
				}
				// Checks if the current lowest motivation cost of the assessments in the list, lowMotivationAssessments,
				// is greater than that of the checking assessment.
				else if (pLowMotivationAssessment->DeferMotivationValue() > pDeferringAssessment->DeferMotivationValue())
				{
					// If so, clears the list, lowMotivationAssessments, and pushes it to the list, lowMotivationAssessments.
					lowMotivationAssessments.clear();
					lowMotivationAssessments.push_back(pDeferringAssessment);
				}
			}
		}
	}
	return lowMotivationAssessments;
}

/**
 * @brief Defers a provided assessment.
 * 
 * Iterates through mPortfolio and removes the assessment weak ptr.
 * Increments motivation by the regainable motivation from deferring.
 * Decrements success by the sacrificable success due to deferring.
 * Removes player from mCompleters in the assessment.
 * 
 * @param[in] pActivity, The assessment to be deferred.
 */
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
					IncrementMotivationBy(pDeferringAssessment->DeferMotivationValue());
					DecrementSuccessBy(pDeferringAssessment->DeferSuccessValue());
					pDeferringAssessment->RemoveCompleter(shared_from_this());
					std::cout << GetName() << " defers " << pDeferringAssessment->GetName();
					std::cout << " for " << pDeferringAssessment->DeferMotivationValue() << '\n';
					break;
				}
			}
		}
	}
}

/**
 * @brief Attempts to regain motivation by deferring low motivation assessments.
 *
 * This method attempts to regain motivation by deferring low motivation assessments in the player's portfolio.
 * It iterates through the portfolio to find assessments with low motivation, prioritizes them based on the current
 * year, and defers them accordingly until motivation is regained or the portfolio becomes empty.
 */
void CPlayer::RegainMotivation()
{
	// Continues until player is motivated or the portfolio is empty.
	while (!IsMotivated() && !mPortfolio.empty())
	{
		// Holds assessments with the lowest motivation cost.
		auto lowMotivationAssessments = GetLowMotivationAssessments();
		// Checks if there's more than one assessments with the lowest motivation cost.
		if (lowMotivationAssessments.size() == 1)
		{
			DeferAssessment(lowMotivationAssessments.front().lock());
			continue;
		}
		// Retrieves the descending order of assessments to defer by year.
		Shorts priorityYears = Prioritize(mYear);
		// Iterates through the priority years.
		for (const auto& priorityYear : priorityYears)
		{
			// Iterates through low motivation assessments.
			for (auto assessment = lowMotivationAssessments.begin(); assessment != lowMotivationAssessments.end(); ++assessment)
			{
				if (auto pAssessment = std::dynamic_pointer_cast<Assessment>(assessment->lock()))
				{
					// Defers assessment.
					if (priorityYear == pAssessment->GetYear())
					{
						DeferAssessment(pAssessment);
					}
				}
				// Checks if deferring more assessments needed.
				if (IsMotivated())
				{
					break;
				}
			}
			// Checks if deferring more assessments needed.
			if (IsMotivated())
			{
				break;
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
 * 
 * @param pActivity[in], The shared ptr of the activity to be completed.
 */
void CPlayer::CompleteActivity(ActivitySharedPtr pActivity)
{
	DecrementMotivationBy(pActivity->GetMotivationCost());
	IncrementSuccessBy(pActivity->GetSuccess());
	if (typeid(*pActivity) == typeid(Assessment))
	{
		std::cout << GetName() << " completes the " << pActivity->GetName();
		
	}
	else
	{
		std::cout << GetName() << " undertakes " << pActivity->GetName() << " activity";
	}
	std::cout << " for " << pActivity->GetMotivationCost() << " and achieves " << pActivity->GetSuccess() << '\n';
	pActivity->GetHelp(GetName());
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
 * 
 * @param[in] kSuccessGain, success to increment.
 * @param[in] kMotivationGain, motivation to increment. 
 * @param[in] kHelpReciever, help recievers name.
 */
void CPlayer::SupportFriend(const unsigned short& kSuccessGain, const unsigned short& kMotivationGain, const std::string& kHelpReciever)
{
	std::cout << kHelpReciever << " motivates " << GetName() << " by " << kMotivationGain << " by joining their activity\n";
	std::cout << GetName() << " also acheives " << kSuccessGain << '\n';
	mSuccess += kSuccessGain;
	mMotivation += kMotivationGain;
}

/**
 * @brief Supports a player by helping their assessment.
 * 
 * Increments success gained by joining the activity.
 * 
 * @param[in] kSuccessGain, success to gain.
 */
void CPlayer::SupportFriend(const unsigned short& kSuccessGain)
{
	std::cout << " ..." << GetName() << " helps and achieves " << kSuccessGain << '\n';
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

/**
 * @brief Resubmits a provided assessment.
 *
 * Iterates through mDeferredPortfolio and removes the assessment weak ptr.
 * Decrements motivation by the defer motivation value to re-submit.
 * Increments success by the defer success value from resubmission.
 * Add player to mCompleters in the assessment.
 *
 * @param[in] pActivity, The assessment to be resubmitted.
 */
void CPlayer::Resubmit(ActivitySharedPtr pActivity)
{
	for (auto assessment = mDeferredPortfolio.begin(); assessment != mDeferredPortfolio.end(); ++assessment)
	{
		if (auto pAssessment = assessment->lock())
		{
			if (pActivity == pAssessment)
			{
				if (auto pResubmission = std::dynamic_pointer_cast<Assessment>(pActivity))
				{
					mDeferredPortfolio.erase(assessment);
					mPortfolio.push_back(pActivity);
					DecrementMotivationBy(pResubmission->DeferMotivationValue());
					IncrementSuccessBy(pResubmission->DeferSuccessValue());
					pResubmission->AddCompleter(shared_from_this());
					std::cout << GetName() << " submits deferred assessment ";
					std::cout << pResubmission->GetName() << " for " << pResubmission->DeferMotivationValue() << '\n';
					break;
				}
			}
		}
	}
}

/**
 * @brief Attempts to resubmit deferred assessments with gained motivation.
 *
 * This method attempts to resubmit assessments in the player's deferred-portfolio by spending gained motivation.
 * It iterates through the deferred-portfolio to find assessments with low motivation, prioritizes them based on the current
 * year, and resubmits them accordingly until the player does not have motivation to resubmit or the deeferred-portfolio becomes empty.
 */
void CPlayer::ResubmitAssessments()
{
	while (!mDeferredPortfolio.empty())
	{
		// Holds assessments with the lowest motivation cost.
		auto lowMotivationAssessments = GetLowMotivationAssessments(true);
		// Checks if resubmission is possible with the current motivation.
		if (auto pFirstAssessment = std::dynamic_pointer_cast<Assessment>(lowMotivationAssessments.front().lock()))
		{
			if (pFirstAssessment->DeferMotivationValue() > mMotivation)
			{
				break;
			}
		}
		// Checks if there's more than one assessments with the lowest motivation cost.
		if (lowMotivationAssessments.size() == 1)
		{
			if (auto pFirstAssessment = std::dynamic_pointer_cast<Assessment>(lowMotivationAssessments.front().lock()))
			{
				Resubmit(pFirstAssessment);
				continue;
			}
		}
		// Retrieves the descending order of assessments to defer by year.
		Shorts priorityYears = Prioritize(mYear);
		// Converts the list into ascending order.
		std::reverse(priorityYears.begin(), priorityYears.end());
		for (const auto& priorityYear : priorityYears)
		{
			// Iterates through low motivation assessments.
			for (auto assessment = lowMotivationAssessments.begin(); assessment != lowMotivationAssessments.end(); ++assessment)
			{
				if (auto pAssessment = std::dynamic_pointer_cast<Assessment>(assessment->lock()))
				{
					
					if (priorityYear == pAssessment->GetYear())
					{
						Resubmit(pAssessment);
					}
				}
				// Checks if resubmission is possible with the current motivation.
				if (auto pFirstAssessment = std::dynamic_pointer_cast<Assessment>(lowMotivationAssessments.front().lock()))
				{
					if (pFirstAssessment->DeferMotivationValue() > mMotivation)
					{
						break;
					}
				}
			}
			// Checks if resubmission is possible with the current motivation.
			if (auto pFirstAssessment = std::dynamic_pointer_cast<Assessment>(lowMotivationAssessments.front().lock()))
			{
				if (pFirstAssessment->DeferMotivationValue() > mMotivation)
				{
					break;
				}
			}
		}
	}
}

int CPlayer::GetSuccess() const
{
	return mSuccess;
}

void CPlayer::DropOut()
{
	for (auto& assessment : mPortfolio)
	{
		if (auto pAssessment = std::dynamic_pointer_cast<Activity>(assessment.lock()))
		{
			pAssessment->RemoveCompleter(shared_from_this());
		}
	}
	for (auto& accomplishment : mAccomplishments)
	{
		if (auto pAccomplishment = std::dynamic_pointer_cast<Activity>(accomplishment.lock()))
		{
			pAccomplishment->RemoveCompleter(shared_from_this());
		}
	}
	std::cout << GetName() << " drops out/n";
}

void CPlayer::PrintStats()
{
	std::cout << GetName() << "'s motivation is " << GetMotivation() << " and success is " << GetSuccess() << "\n\n";
}