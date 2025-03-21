#include <iostream>
#include "game_logic/board.h"

int main() {
    srand(time(0));
    addRandomTile();
    addRandomTile();
    printBoard();

    char move;
    while (true) {
        std::cout << "Enter move (W/A/S/D to move, Q to quit): ";
        std::cin >> move;
        move = toupper(move);  // Chuyển thành chữ hoa

        bool moved = false;
        if (move == 'Q') break;
        else if (move == 'W') moved = moveUp();
        else if (move == 'S') moved = moveDown();
        else if (move == 'A') moved = moveLeft();
        else if (move == 'D') moved = moveRight();
        else {
            std::cout << "Invalid move! Use W/A/S/D or Q to quit." << std::endl;
            continue;
        }

        if (moved) {
            addRandomTile();
        }
        printBoard();
    }

    std::cout << "Game over!" << std::endl;
    return 0;
}