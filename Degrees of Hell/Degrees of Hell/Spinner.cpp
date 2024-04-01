#include "Spinner.h"
#include <iostream>

/**
 * @brief Simulates spinning the spinner and returns a random integer between 1 and 10.
 *
 * If the spinner is not seeded, seeds the random number generator with the specified seed value.
 * Generates a random number using rand() and scales it to produce a value between 1 and 10.
 *
 * @return A random integer between 1 and 10.
 */
int Spinner::Spin(const std::string& kName)
{
    if (!mSeeded)
    {
        srand(mSeed);
        mSeeded = true;
    }
    int num = static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 10.0f + 1);
    std::cout << kName << " spins " << num << '\n';
    return num;
}

/**
 * @brief Constructs a Spinner object with the specified seed value.
 * 
 * @param[in] kSeed, The seed value to initialize the Spinner with.
 */
Spinner::Spinner(const int& kSeed)
{
    mSeed = kSeed;
}