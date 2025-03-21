#include <iostream>
#include "game_logic/board.h"

int main() {
    srand(time(0));
    addRandomTile();
    addRandomTile();
    printBoard();
    return 0;
}