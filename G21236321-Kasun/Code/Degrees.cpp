#include "Degrees.h"

/**
 * @brief Constructor.
 * 
 * Populates players with the playerNames in mPlayers.
 * Creates a data-reading object and reads seed and create a spinner object with the seed.
 * Craetes board object.
 * Assigns kNumOfRounds to mNumOfRounds.
 * 
 * @param[in] playerNames, The names of the players.
 * @param[in] kSeedFileName, The file name of the file containing the seed for the spinner.
 * @param[in] kDegreesFileName, The file name of the file containing the data for the board.
 * @param[in] kNumOfRounds, The number of round to played.
 */
Degrees::Degrees(Strings playerNames, const std::string& kSeedFileName, const std::string& kDegreesFileName, const int& kNumOfRounds)
{
	for (const auto& playerName : playerNames)
	{
		mPlayers.push_back(std::make_shared<CPlayer>(playerName));;
	}
	std::shared_ptr<DataReading> pDataReader = std::make_shared<DataReading>();
	mpSpinner = std::make_shared<Spinner>(pDataReader->GetSeed(kSeedFileName));
	mpBoard = std::make_shared<Board>(kDegreesFileName, mpSpinner);
	mNumOfRounds = kNumOfRounds;
}

/**
 * @brief Kicks a player out of the game.
 * @param[] pDropper, The player to be removed.
 */
void Degrees::KickOut(std::shared_ptr<CPlayer> pDropper)
{
	for (auto pPlayer = mPlayers.begin(); pPlayer != mPlayers.end(); ++pPlayer)
	{
		if (*pPlayer == pDropper)
		{
			pDropper->DropOut();
			mPlayers.erase(pPlayer);
			break;
		}
	}
}

/**
 * @brief Prints round number.
 */
void Degrees::PrintRoundNumber() const
{
	std::cout << "ROUND " << mRound << '\n';
	std::cout << "=========\n";
}

/**
 * @brief Prints completion of a year by a player.
 * @param[in] kName, The player name.
 * @param[in] kYear, The year.
 */
void Degrees::PrintYearCompletion(const std::string& kName, const short& kYear)
{
	std::cout << kName << " has successfully completed Year " << kYear << '\n';
}

/**
 * @brief Prints the winner of the game.
 * @param[in] kName, The player name.
 */
void Degrees::PrintWinner(const std::string& kName)
{
	std::cout << "Congratulations to " << kName << " on their Graduation Day!\n";
	std::cout << "Game Over\n";
	std::cout << "=========\n\n";
	std::cout << kName << " Wins!\n";
}

/**
 * @brief Prints a player starting a new year
 * @param[in] kName, The name of the player.
 * @param[in] kYear, The year.
 */
void Degrees::PrintStartingNewYear(const std::string& kName, const short& kYear)
{
	std::cout << kName << " attends Welcome Week and starts Year " << kYear << '\n';
}

/**
 * @brief Prints a player repeating the same year
 * @param[in] kName, The name of the player.
 * @param[in] kYear, The year.
 */
void Degrees::PrintRepeatingYear(const std::string& kName, const short& kYear)
{
	std::cout << kName << " attends Welcome Week and starts Year " << kYear << " again\n";
}

/**
 * @brief Prints game over when there is no players left.
 */
void Degrees::PrintEmptyPlayers()
{
	std::cout << "Game Over\n";
	std::cout << "=========\n\n";
	std::cout << "Nobody Wins!\n";
}

/**
 * @brief Prints game over when there is no more rounds left to play.
 */
void Degrees::PrintRoundOver()
{
	std::cout << "Game Over\n";
	std::cout << "=========\n\n";
	std::cout << "Rounds Over!\n";
}

/**
 * @brief Prints welcome to the game.
 */
void Degrees::PrintWelcome()
{
	std::cout << "Welcome to Scumbag College\n\n";
}

/**
 * @brief The game loop.
 */
void Degrees::GameLoop()
{
	// Bool to track the game status.
	bool gameOver = false;
	while (!gameOver)
	{
		// Prints round number.
		PrintRoundNumber();
		// Iterates through mPlayers.
		for (auto& pPlayer : mPlayers)
		{
			// The player spins.
			short spinNum = mpSpinner->Spin(pPlayer->GetName());
			// Stores the new position player about to move.
			short newIndex = pPlayer->GetPosition() + spinNum;
			// Checks if the new position is out of the range.
			// If it is, it means the player a chance to advance next year or graduate.
			if (newIndex >= mpBoard->Length())
			{
				// Checks if the player has completed three assessments of the current year.
				if (pPlayer->CanAdvance(mkMinNumAssessments))
				{
					// Prints about the player's year completion.
					PrintYearCompletion(pPlayer->GetName(), pPlayer->GetYear());
					// Checks if the completed year is the graduation year.
					if (pPlayer->GetYear() == mkGraduationYear)
					{
						// The player graduates and wins the game.
						PrintWinner(pPlayer->GetName());
						// Sets game over status.
						gameOver = true;
						break;
					}
					// Increments year if the player didn't graduate.
					pPlayer->IncrementYear();
					// Prints about starting a new year.
					PrintStartingNewYear(pPlayer->GetName(), pPlayer->GetYear());
				}
				else
				{
					// The player had not done three assessments, so the player repeats the year.
					PrintRepeatingYear(pPlayer->GetName(), pPlayer->GetYear());
				}
				// Increments motivation for passing the welcome week.
				pPlayer->IncrementMotivationBy(mkNewYearMotivation);
				// Corrects the new position the player about to move.
				newIndex = newIndex % mpBoard->Length();
			}
			// Sets player position to new position.
			pPlayer->SetPosition(newIndex);
			// Player lands on the new position.
			mpBoard->Lands(pPlayer, newIndex);
			// Checks if the player has positive motivation.
			if (pPlayer->IsMotivated())
			{
				// Attempts re-submit deferred assessments.
				pPlayer->ResubmitAssessments();
			}
			else
			{
				// Tries to gain motivation by deferring assessments.
				pPlayer->RegainMotivation();
			}
			// If the player does not have a positive motivation after
			// deferring all the assessments, remove them.
			if (!pPlayer->IsMotivated())
			{
				KickOut(pPlayer);
			}
			// Checks if the pPlayer is a nullptr incase the player dropped out.
			if (pPlayer)
			{
				// Prints player motivation and success.
				pPlayer->PrintStats();
			}
		}
		// Checks if all the players have dropped out.
		if (mPlayers.empty())
		{
			PrintEmptyPlayers();
			gameOver = true;
		}
		// Increments the round number.
		mRound++;
		// Checks if the round number exceeds the given number of rounds.
		if (mNumOfRounds < mRound)
		{
			PrintRoundOver();
			gameOver = true;
		}
	}
}

/**
 * @brief Starts the whole game.
 */
void Degrees::Start()
{
	PrintWelcome();
	GameLoop();
}