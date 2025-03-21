#include <iostream>
#include "game_logic/board.h"

// Hàm xóa màn hình console (Windows)
void clearScreen() {
    system("cls");
}

int main() {
    srand(time(0));
    addRandomTile();
    addRandomTile();
    clearScreen();
    printBoard();

    char move;
    while (true) {
        std::cout << "Enter move (W/A/S/D to move, Q to quit): ";
        std::cin >> move;
        move = toupper(move);

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

        clearScreen();
        printBoard();

        if (checkWin()) {
            std::cout << "You win!" << std::endl;
            break;
        }
        if (checkLose()) {
            std::cout << "Game over! You lose!" << std::endl;
            break;
        }
    }

    return 0;
}