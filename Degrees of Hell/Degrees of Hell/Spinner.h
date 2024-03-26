#ifndef SPINNER
#define SPINNER

// Represents a spinner for generating random numbers with a seed value.
class Spinner
{
private:
    // The seed
    int mSeed = 0;
    // Keeps track if the random number generator is seeded or not.
    bool mSeeded = false;
public:
    int Spin();
    Spinner(const int&);
};

#endif