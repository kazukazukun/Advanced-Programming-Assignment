#include "Degrees.h"

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

void Degrees::PrintRoundNumber() const
{
	std::cout << "ROUND " << mRound << '\n';
	std::cout << "=========\n";
}

void Degrees::PrintYearCompletion(const std::string& kName, const short& kYear)
{
	std::cout << kName << " has successfully completed Year " << kYear << '\n';
}

void Degrees::PrintWinner(const std::string& kName)
{
	std::cout << "Congratulations to " << kName << " on their Graduation Day!\n";
	std::cout << "Game Over\n";
	std::cout << "=========\n\n";
	std::cout << kName << " Wins!\n";
}

void Degrees::PrintStartingNewYear(const std::string& kName, const short& kYear)
{
	std::cout << kName << " attends Welcome Week and starts Year " << kYear << '\n';
}

void Degrees::PrintRepeatingYear(const std::string& kName, const short& kYear)
{
	std::cout << kName << " attends Welcome Week and starts Year " << kYear << " again\n";
}

void Degrees::PrintEmptyPlayers()
{
	std::cout << "Game Over\n";
	std::cout << "=========\n\n";
	std::cout << "Nobody Wins!\n";
}

void Degrees::PrintRoundOver()
{
	std::cout << "Game Over\n";
	std::cout << "=========\n\n";
	std::cout << "Rounds Over!\n";
}

void Degrees::PrintWelcome()
{
	std::cout << "Welcome to Scumbag College\n\n";
}

void Degrees::GameLoop()
{
	bool gameOver = false;
	while (!gameOver)
	{
		PrintRoundNumber();
		for (auto& pPlayer : mPlayers)
		{
			short spinNum = mpSpinner->Spin(pPlayer->GetName());
			short newIndex = pPlayer->GetPosition() + spinNum;
			if (newIndex >= mpBoard->Length())
			{
				if (pPlayer->CanAdvance(mkMinNumAssessments))
				{
					PrintYearCompletion(pPlayer->GetName(), pPlayer->GetYear());
					if (pPlayer->GetYear() == mkGraduationYear)
					{
						PrintWinner(pPlayer->GetName());
						gameOver = true;
						break;
					}
					pPlayer->IncrementYear();
					PrintStartingNewYear(pPlayer->GetName(), pPlayer->GetYear());
				}
				else
				{
					PrintRepeatingYear(pPlayer->GetName(), pPlayer->GetYear());
				}
				pPlayer->IncrementMotivationBy(mkNewYearMotivation);
				newIndex = newIndex % mpBoard->Length();
			}
			pPlayer->SetPosition(newIndex);
			mpBoard->Lands(pPlayer, newIndex);
			if (pPlayer->IsMotivated())
			{
				pPlayer->ResubmitAssessments();
			}
			else
			{
				pPlayer->RegainMotivation();
			}
			if (!pPlayer->IsMotivated())
			{
				KickOut(pPlayer);
			}
			if (pPlayer)
			{
				pPlayer->PrintStats();
			}
		}
		if (mPlayers.empty())
		{
			PrintEmptyPlayers();
			gameOver = true;
		}
		mRound++;
		if (mNumOfRounds < mRound)
		{
			PrintRoundOver();
			gameOver = true;
		}
	}
}

void Degrees::Start()
{
	PrintWelcome();
	GameLoop();
}