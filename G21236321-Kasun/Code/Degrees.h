#pragma once

#include "Spinner.h"
#include "DataReading.h"
#include "Board.h"
#include "CPlayer.h"
#include "Spinner.h"

class Degrees
{
private:
	// Holds players.
	Players mPlayers;
	// Holds round number.
	unsigned int mRound = 1;
	// Total number of rounds.
	unsigned int mNumOfRounds = 500;
	// Holds motivation gain per round.
	const unsigned int mkNewYearMotivation = 250;
	// Holds graduation year.
	const unsigned short mkGraduationYear = 3;
	// Holds the minimum number of assessments, a player needs to advance to
	// next year or graduate.
	const unsigned short mkMinNumAssessments = 3;
	// Holds Spinner
	std::shared_ptr<Spinner> mpSpinner;
	// Holds Game Board.
	std::shared_ptr<Board> mpBoard = nullptr;

	void KickOut(std::shared_ptr<CPlayer>);
	void GameLoop();
	void PrintRoundNumber() const;
	void PrintYearCompletion(const std::string&, const short&);
	void PrintWinner(const std::string&);
	void PrintStartingNewYear(const std::string&, const short&);
	void PrintRepeatingYear(const std::string&, const short&);
	void PrintEmptyPlayers();
	void PrintRoundOver();
	void PrintWelcome();

public:
	Degrees(Strings, const std::string&, const std::string&, const int&);
	void Start();
};

