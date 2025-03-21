#include <iostream>
#include <iomanip>
#include "board.h"

int board[SIZE][SIZE] = {0};
int score = 0;  // Khởi tạo điểm số

void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                std::cout << std::setw(4) << ".";
            } else {
                std::cout << std::setw(4) << board[i][j];
            }
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

bool moveLeft() {
    bool moved = false;
    for (int i = 0; i < SIZE; i++) {
        int k = 0;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                if (k > 0 && board[i][k-1] == board[i][j]) {
                    board[i][k-1] *= 2;
                    score += board[i][k-1];  // Cộng điểm
                    board[i][j] = 0;
                    moved = true;
                } else {
                    if (k != j) {
                        board[i][k] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    k++;
                }
            }
        }
    }
    return moved;
}

bool moveRight() {
    bool moved = false;
    for (int i = 0; i < SIZE; i++) {
        int k = SIZE - 1;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (k < SIZE - 1 && board[i][k+1] == board[i][j]) {
                    board[i][k+1] *= 2;
                    score += board[i][k+1];  // Cộng điểm
                    board[i][j] = 0;
                    moved = true;
                } else {
                    if (k != j) {
                        board[i][k] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    k--;
                }
            }
        }
    }
    return moved;
}

bool moveUp() {
    bool moved = false;
    for (int j = 0; j < SIZE; j++) {
        int k = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] != 0) {
                if (k > 0 && board[k-1][j] == board[i][j]) {
                    board[k-1][j] *= 2;
                    score += board[k-1][j];  // Cộng điểm
                    board[i][j] = 0;
                    moved = true;
                } else {
                    if (k != i) {
                        board[k][j] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    k++;
                }
            }
        }
    }
    return moved;
}

bool moveDown() {
    bool moved = false;
    for (int j = 0; j < SIZE; j++) {
        int k = SIZE - 1;
        for (int i = SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (k < SIZE - 1 && board[k+1][j] == board[i][j]) {
                    board[k+1][j] *= 2;
                    score += board[k+1][j];  // Cộng điểm
                    board[i][j] = 0;
                    moved = true;
                } else {
                    if (k != i) {
                        board[k][j] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    k--;
                }
            }
        }
    }
    return moved;
}

bool checkWin() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == WIN_VALUE) {
                return true;
            }
        }
    }
    return false;
}

bool checkLose() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) {
                return false;
            }
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) {
                return false;
            }
        }
    }

    return true;
}

int getScore() {
    return score;
}