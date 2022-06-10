#include <vector>
#include <ctime>
#include <fstream>
#include "Game.h"

using namespace std;

int main()
{
    srand(time(0));
    setlocale(0, "Russian");
    DoodleJumpV1::Game game;
    game.Controller();
    return 0;
}