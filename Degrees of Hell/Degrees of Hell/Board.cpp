#include "Board.h"
#include "AccusedOfPlagiarism.h"
#include "Assessment.h"
#include "Bogus.h"
#include "Bonus.h"
#include "ExtraCurricular.h"
#include "PlagiarismHearing.h"
#include "SkipClasses.h"
#include "WelcomeWeek.h"
#include <memory>
#include <string>

/**
 * @brief Creates a board with using provided params.
 * 
 * Reads from file and populates mSpaces.
 * 
 * @param[in] kFileName, Name of the file conatianing the game input data.
 * @param[in] pSpinner, The weak ptr of the spinner object created in the game.
 */
Board::Board(const std::string& kFileName, std::weak_ptr<Spinner> pSpinner)
{
    std::shared_ptr<DataReading> pDataReader = std::make_shared<DataReading>();
    Populate(pDataReader->GetCSpaces(kFileName), pSpinner);
    short index = 0;
    std::weak_ptr<PlagiarismHearing> pPlagSpace = FindPlagiarismHearingSpace(index);
    NotifyPlagiarismSpaces(index, pPlagSpace);
}

/**
 * @brief Finds the index and the weak ptr of the  Plagiarism Hearing space.
 * 
 * @param[in, out] index, To retrieve the index of the  Plagiarism Hearing space.
 * 
 * @return The weak ptr of the Plagiarism Hearing space.
 */
std::weak_ptr<PlagiarismHearing> Board::FindPlagiarismHearingSpace(short& index)
{
    index = 0;
    for (const auto& pSpace : mSpaces)
    {
        if (std::dynamic_pointer_cast<PlagiarismHearing>(pSpace))
        {
            return std::dynamic_pointer_cast<PlagiarismHearing>(pSpace);
        }
        index++;
    }
    return std::weak_ptr<PlagiarismHearing>();
}

/**
 * @brief Sets PlagiarismHearing index and weak ptr to AccusedOfPlagiarism spaces. 
 * @param[in] kIndex, PlagiarismHearing index.
 * @param[in] pPlagSpace, PlagiarismHearing weak ptr.
 */
void Board::NotifyPlagiarismSpaces(const short& kIndex, std::weak_ptr<PlagiarismHearing> pPlagSpace)
{
    for (const auto& pSpace : mSpaces)
    {
        if (auto pAccOfPlagSpace = std::dynamic_pointer_cast<AccusedOfPlagiarism>(pSpace))
        {
            pAccOfPlagSpace->SetHearingSpace(kIndex, pPlagSpace);
        }
    }
}

/**
 * @brief Merges if there are consecutive elements which cannot
 * be assigned to an int, in the provided vector of strings.
 * 
 * @param[in, out] list, The provided vector of strings.
 * 
 * @return list, The modified vector of strings.
 */
Strings Board::MergeStrings(Strings list)
{
    // Iterate through the list.
    for (auto element = list.begin(); element != list.end(); ++element)
    {
        // Check if the current string to int convertion is possible.
        std::istringstream currentString(*element);
        std::istringstream nextString(*(element + 1));
        int intValue = 0;
        if (!(currentString >> intValue))
        {
            // If the current string cannot be converted to an integer,
            // check the next element
            auto nextElement = element + 1;
            // Checks if the next element is not the end of the vactor and
            // checks if the next element to int convertion is possible.
            if (nextElement != list.end() && !(nextString >> intValue))
            {
                // Combine the current and next elements.
                std::string combinedElement = *element + " " + *nextElement;
                *element = combinedElement;
                // Erase the next element.
                list.erase(nextElement);
                // Checks if the new next element to int convertion is possible.
                nextElement = element + 1;
                std::istringstream nextString(*nextElement);
                if (!(nextString >> intValue))
                {
                    // Move the iterator back to combine the current string and next string.
                    element--;
                }
            }
        }
    }
    return list;
}

/**
 * @brief Splits provided string by spaces.
 * 
 * Splits provided string by spaces,
 * adds them to a vector of string and
 * returns it.
 * 
 * @param[in] kInput, The string to be split. 
 * @return list, The vector of strings containing the splits.
 */
Strings Board::Split(const std::string& kInput)
{
    std::istringstream currentString(kInput);
    std::vector<std::string> list;
    std::string tempString;

    while (currentString >> tempString)
    {
        list.push_back(tempString);
    }
    return list;
}

/**
 * @brief Populates pSpaces with given data.
 * 
 * Accepts a vector of strings and a weak ptr to the spinner created in the degrees class.
 * Formats data into usable format.
 * Creates objects based on the type id of the reading.
 * 
 * @param[in] dataReadings, The vector of string containing the data.
 * @param[in] pSpinner, The weak ptr of the spinner. To create Bonus and Bogus objects.
 */
void Board::Populate(Strings dataReadings, std::weak_ptr<Spinner> pSpinner)
{
    for (auto& pData : dataReadings)
    {
        if (!pData.empty()) {
            Strings params = MergeStrings(Split(pData));
            switch (std::stoi(std::string(1, pData[0])))
            {
            case 1: // Assessment
                mSpaces.push_back(std::make_shared<Assessment>(params[1],
                    std::stoi(params[2]), std::stoi(params[3]), std::stoi(params[4])));
                break;
            case 2: // Welcome Week
                mSpaces.push_back(std::make_shared<WelcomeWeek>(params[1]));
                break;
            case 3: // Extra - curricular Activity
                mSpaces.push_back(std::make_shared<ExtraCurricular>(params[1], std::stoi(params[2]), mExtraCurricularSuccess));
                break;
            case 4: // Bonus
                mSpaces.push_back(std::make_shared<Bonus>(params[1], pSpinner));
                break;
            case 5: // Bogus
                mSpaces.push_back(std::make_shared<Bogus>(params[1], pSpinner));
                break;
            case 6: // Plagiarism Hearing
                mSpaces.push_back(std::make_shared<PlagiarismHearing>(params[1]));
                break;
            case 7: // Accused of Plagiarism
                mSpaces.push_back(std::make_shared<AccusedOfPlagiarism>(params[1]));
                break;
            case 8: // Skip Classes
                mSpaces.push_back(std::make_shared<SkipClasses>(params[1]));
                break;
            }
        }
    }
}


void Board::Lands(std::shared_ptr<CPlayer> pPlayer, const short& kIndex)
{
    mSpaces[kIndex]->Lands(pPlayer);
}

short Board::Length()
{
    return mSpaces.size();
}