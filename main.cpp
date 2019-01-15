#include "Game.hpp"

int main(int argc, char** argv)  {
    int size = atoi(argv[1]), mines = atoi(argv[2]);
    Game game(size, mines);
    return 0;
}