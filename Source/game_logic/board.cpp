#include <iostream>
#include "board.h"

int board[SIZE][SIZE] = {0};

void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << board[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "------------" << std::endl;
}

void addRandomTile() {
    int empty = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) empty++;
        }
    }

    if (empty > 0) {
        int pos = rand() % empty;
        int count = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0) {
                    if (count == pos) {
                        board[i][j] = (rand() % 2 + 1) * 2;
                        return;
                    }
                    count++;
                }
            }
        }
    }
}