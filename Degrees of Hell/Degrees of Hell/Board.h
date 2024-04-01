#pragma once

#include "CSpace.h"
#include "DataReading.h"
#include "Spinner.h"
#include <sstream>
#include <string>

class Board
{
private:
	Spaces mSpaces;
	const short mExtraCurricularSuccess = 20;
	Strings MergeStrings(Strings);
	Strings Split(const std::string&);
	void Populate(Strings, std::weak_ptr<Spinner>);
public:
	Board(const std::string&, std::weak_ptr<Spinner>);
};

