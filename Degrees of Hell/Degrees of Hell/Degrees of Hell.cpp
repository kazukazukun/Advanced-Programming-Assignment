#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Degrees.h"
#include <crtdbg.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::vector<std::string> players = {"Vyvyan", "Rick", "Neil", "Mike"};
    std::string seedFile = "seed.txt";
    std::string degreesFile = "degrees.txt";
    int numOfRounds = 50;
    std::shared_ptr<Degrees> game = std::make_shared<Degrees>(players, seedFile, degreesFile, numOfRounds);
    game->Start();
    return 0;
}
