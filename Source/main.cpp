#include <iostream>
#include "game_logic/board.h"

void clearScreen() {
    system("cls");
}

int main() {
    srand(time(0));
    Board game;  // Tạo đối tượng Board
    game.loadHighScore();  // Tải high score khi bắt đầu
    clearScreen();
    std::cout << "Welcome to 2048!" << std::endl;
    std::cout << "High Score: " << game.getHighScore() << std::endl;
    std::cout << "Use W/A/S/D to move, Q to quit, P to save." << std::endl;
    std::cout << "Reach 2048 to win!" << std::endl;
    std::cout << "1. Start new game" << std::endl;
    std::cout << "2. Load saved game" << std::endl;
    std::cout << "Enter your choice (1 or 2): ";
    int choice;
    std::cin >> choice;

    clearScreen();
    if (choice == 2 && game.loadGame()) {
        // Tải thành công, tiếp tục chơi
    } else {
        // Bắt đầu trò chơi mới
        game.addRandomTile();
        game.addRandomTile();
    }

    std::cout << "Score: " << game.getScore() << std::endl;
    game.printBoard();

    char move;
    while (true) {
        std::cout << "Enter move (W/A/S/D to move, Q to quit, P to save): ";
        std::cin >> move;
        move = toupper(move);

        bool moved = false;
        if (move == 'Q') break;
        else if (move == 'P') {
            game.saveGame();
            continue;
        }
        else if (move == 'W') moved = game.moveUp();
        else if (move == 'S') moved = game.moveDown();
        else if (move == 'A') moved = game.moveLeft();
        else if (move == 'D') moved = game.moveRight();
        else {
            std::cout << "Invalid move! Use W/A/S/D, Q to quit, or P to save." << std::endl;
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            continue;
        }

        if (moved) {
            game.addRandomTile();
        }

        clearScreen();
        std::cout << "Score: " << game.getScore() << std::endl;
        game.printBoard();

        if (game.checkWin()) {
            std::cout << "You win! Final score: " << game.getScore() << std::endl;
            game.saveHighScore();  // Cập nhật high score
            std::cout << "New High Score: " << game.getHighScore() << std::endl;
            break;
        }
        if (game.checkLose()) {
            std::cout << "Game over! You lose! Final score: " << game.getScore() << std::endl;
            game.saveHighScore();  // Cập nhật high score
            std::cout << "High Score: " << game.getHighScore() << std::endl;
            break;
        }
    }

    return 0;
}