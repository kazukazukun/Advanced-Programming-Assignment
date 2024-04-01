#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Degrees.h"
#include "Spinner.h"
#include <crtdbg.h>

// Main method.
int main()
{
    // Checks if there are any memory leaks in the program.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Declares player names.
    std::string playerOne = "Vyvyan";
    std::string playerTwo = "Rick";
    std::string playerThree = "Neil";
    std::string playerFour = "Mike";

    // Assigns all the players to one vector.
    Strings players = {playerOne , playerTwo, playerThree, playerFour };

    // File name of the file containing the seed for spinner.
    std::string seedFile = "seed.txt";
    // File name of the file containing the data for spaces in the board.
    std::string degreesFile = "degrees.txt";

    // Number of rounds.
    int numOfRounds = 500;

    // Creates a Degrees object to a shared pointer with the params.
    std::shared_ptr<Degrees> pGame = std::make_shared<Degrees>(players, seedFile, degreesFile, numOfRounds);

    // Starts the game.
    pGame->Start();

    return 0;
}
