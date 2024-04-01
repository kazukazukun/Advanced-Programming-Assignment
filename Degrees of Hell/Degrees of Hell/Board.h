#pragma once

#include "CSpace.h"
#include "DataReading.h"
#include "Spinner.h"
#include "PlagiarismHearing.h"
#include "CPlayer.h"
#include <sstream>
#include <string>

// Class to represent the board of the game.
class Board
{
private:
	// CSpace type shared ptr vector to hold spaces of the board.
	Spaces mSpaces;
	// Success gain for extra-curricular activities.
	const short mExtraCurricularSuccess = 20;

	Strings MergeStrings(Strings);
	Strings Split(const std::string&);
	void Populate(Strings, std::weak_ptr<Spinner>);
	std::weak_ptr<PlagiarismHearing> FindPlagiarismHearingSpace(short&);
	void NotifyPlagiarismSpaces(const short&, std::weak_ptr<PlagiarismHearing>);
public:
	Board(const std::string&, std::weak_ptr<Spinner>);
	void Lands(std::shared_ptr<CPlayer>, const short&);
	short Length();
};

