#include "Mystery.h"

Mystery::Mystery(const std::string& kName, std::weak_ptr<Spinner> pSpinner) : CSpace(kName)
{
	mpSpinner = pSpinner;
}