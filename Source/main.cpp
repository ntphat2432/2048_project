#include <iostream>
#include "game_logic/board.h"

void clearScreen() {
    system("cls");
}

int main() {
    srand(time(0));
    clearScreen();
    std::cout << "Welcome to 2048!" << std::endl;
    std::cout << "Use W/A/S/D to move, Q to quit, P to save." << std::endl;
    std::cout << "Reach 2048 to win!" << std::endl;
    std::cout << "1. Start new game" << std::endl;
    std::cout << "2. Load saved game" << std::endl;
    std::cout << "Enter your choice (1 or 2): ";
    int choice;
    std::cin >> choice;

    clearScreen();
    if (choice == 2 && loadGame()) {
        // Tải thành công, tiếp tục chơi
    } else {
        // Bắt đầu trò chơi mới
        addRandomTile();
        addRandomTile();
    }

    std::cout << "Score: " << getScore() << std::endl;
    printBoard();

    char move;
    while (true) {
        std::cout << "Enter move (W/A/S/D to move, Q to quit, P to save): ";
        std::cin >> move;
        move = toupper(move);

        bool moved = false;
        if (move == 'Q') break;
        else if (move == 'P') {  // Sửa phím S thành P để lưu trò chơi
            saveGame();
            continue;
        }
        else if (move == 'W') moved = moveUp();
        else if (move == 'S') moved = moveDown();  // Phím S giờ chỉ dùng để di chuyển xuống
        else if (move == 'A') moved = moveLeft();
        else if (move == 'D') moved = moveRight();
        else {
            std::cout << "Invalid move! Use W/A/S/D, Q to quit, or P to save." << std::endl;
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            continue;
        }

        if (moved) {
            addRandomTile();
        }

        clearScreen();
        std::cout << "Score: " << getScore() << std::endl;
        printBoard();

        if (checkWin()) {
            std::cout << "You win! Final score: " << getScore() << std::endl;
            break;
        }
        if (checkLose()) {
            std::cout << "Game over! You lose! Final score: " << getScore() << std::endl;
            break;
        }
    }

    return 0;
}