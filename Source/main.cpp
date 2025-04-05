#include <iostream>
#include <string>
#include "game_logic/board.h"

void clearScreen() {
    system("cls");
}

int main() {
    srand(time(0));
    Board game;

    // Giao diện đăng nhập/đăng ký
    clearScreen();
    std::string username, password;
    int choice;
    bool loggedIn = false;

    while (!loggedIn) {
        std::cout << "Welcome to 2048!" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Register" << std::endl;
        std::cout << "Enter your choice (1 or 2): ";
        std::cin >> choice;

        if (choice != 1 && choice != 2) {
            std::cout << "Invalid choice! Please choose 1 or 2." << std::endl;
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            clearScreen();
            continue;
        }

        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        if (choice == 1) {
            // Đăng nhập
            if (game.login(username, password)) {
                std::cout << "Login successful! Welcome, " << username << "!" << std::endl;
                loggedIn = true;
            } else {
                std::cout << "Login failed! Invalid username or password." << std::endl;
            }
        } else {
            // Đăng ký
            if (game.registerUser(username, password)) {
                std::cout << "Registration successful! Welcome, " << username << "!" << std::endl;
                loggedIn = true;
            } else {
                std::cout << "Registration failed! Username already exists." << std::endl;
            }
        }

        if (!loggedIn) {
            std::cout << "Press Enter to try again..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            clearScreen();
        }
    }

    // Tải high score của người dùng
    game.loadHighScore();

    // Giao diện trò chơi
    clearScreen();
    std::cout << "Welcome to 2048, " << game.getCurrentUser() << "!" << std::endl;
    std::cout << "High Score: " << game.getHighScore() << std::endl;
    std::cout << "Use W/A/S/D to move, Q to quit, P to save, U to undo." << std::endl;
    std::cout << "Reach 2048 to win!" << std::endl;
    std::cout << "1. Start new game" << std::endl;
    std::cout << "2. Load saved game" << std::endl;
    std::cout << "Enter your choice (1 or 2): ";
    int choiceGame;
    std::cin >> choiceGame;

    clearScreen();
    if (choiceGame == 2 && game.loadGame()) {
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
        std::cout << "Enter move (W/A/S/D to move, Q to quit, P to save, U to undo): ";
        std::cin >> move;
        move = toupper(move);

        bool moved = false;
        if (move == 'Q') break;
        else if (move == 'P') {
            game.saveGame();
            continue;
        }
        else if (move == 'U') {
            if (game.canUndoMove()) {
                game.undo();
                clearScreen();
                std::cout << "Move undone!" << std::endl;
                std::cout << "Score: " << game.getScore() << std::endl;
                game.printBoard();
            } else {
                std::cout << "Cannot undo!" << std::endl;
                std::cout << "Press Enter to continue..." << std::endl;
                std::cin.ignore();
                std::cin.get();
            }
            continue;
        }
        else if (move == 'W') {
            game.saveState();
            moved = game.moveUp();
        }
        else if (move == 'S') {
            game.saveState();
            moved = game.moveDown();
        }
        else if (move == 'A') {
            game.saveState();
            moved = game.moveLeft();
        }
        else if (move == 'D') {
            game.saveState();
            moved = game.moveRight();
        }
        else {
            std::cout << "Invalid move! Use W/A/S/D, Q to quit, P to save, U to undo." << std::endl;
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
            game.saveHighScore();
            std::cout << "New High Score: " << game.getHighScore() << std::endl;
            break;
        }
        if (game.checkLose()) {
            std::cout << "Game over! You lose! Final score: " << game.getScore() << std::endl;
            game.saveHighScore();
            std::cout << "High Score: " << game.getHighScore() << std::endl;
            break;
        }
    }

    return 0;
}