#include "Mystery.h"

/**
 * @brief Constructor.
 * @param[in] kName, The name of the space.
 * @param[in] pSpinner, The weak ptr of the spinner created in the game.
 */
Mystery::Mystery(const std::string& kName, std::weak_ptr<Spinner> pSpinner) : CSpace(kName)
{
	mpSpinner = pSpinner;
}