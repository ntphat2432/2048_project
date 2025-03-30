#include <iostream>
#include <iomanip>
#include <fstream>  // Thêm để dùng file
#include "board.h"

int board[SIZE][SIZE] = {0};
int score = 0;

// In bảng 4x4 ra console, thay số 0 bằng dấu chấm và căn chỉnh ô
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

// Thêm một ô ngẫu nhiên (2 hoặc 4) vào vị trí trống trên bảng
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

// Di chuyển và hợp nhất ô sang trái, trả về true nếu có thay đổi
bool moveLeft() {
    bool moved = false;
    for (int i = 0; i < SIZE; i++) {
        int k = 0;  // Vị trí tiếp theo để đặt ô
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                if (k > 0 && board[i][k-1] == board[i][j]) {
                    // Hợp nhất ô nếu giống nhau
                    board[i][k-1] *= 2;
                    score += board[i][k-1];  // Cộng điểm
                    board[i][j] = 0;
                    moved = true;
                } else {
                    if (k != j) {
                        // Di chuyển ô nếu vị trí thay đổi
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

// Di chuyển và hợp nhất ô sang phải, trả về true nếu có thay đổi
bool moveRight() {
    bool moved = false;
    for (int i = 0; i < SIZE; i++) {
        int k = SIZE - 1;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (k < SIZE - 1 && board[i][k+1] == board[i][j]) {
                    board[i][k+1] *= 2;
                    score += board[i][k+1];
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

// Di chuyển và hợp nhất ô lên trên, trả về true nếu có thay đổi
bool moveUp() {
    bool moved = false;
    for (int j = 0; j < SIZE; j++) {
        int k = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] != 0) {
                if (k > 0 && board[k-1][j] == board[i][j]) {
                    board[k-1][j] *= 2;
                    score += board[k-1][j];
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

// Di chuyển và hợp nhất ô xuống dưới, trả về true nếu có thay đổi
bool moveDown() {
    bool moved = false;
    for (int j = 0; j < SIZE; j++) {
        int k = SIZE - 1;
        for (int i = SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (k < SIZE - 1 && board[k+1][j] == board[i][j]) {
                    board[k+1][j] *= 2;
                    score += board[k+1][j];
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

// Kiểm tra điều kiện thắng: trả về true nếu có ô đạt 2048
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

// Kiểm tra điều kiện thua: trả về true nếu không còn ô trống và không thể hợp nhất
bool checkLose() {
    // Kiểm tra ô trống
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    // Kiểm tra khả năng hợp nhất
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

// Trả về điểm số hiện tại
int getScore() {
    return score;
}

// Lưu trạng thái trò chơi (bảng và điểm số) vào file
void saveGame() {
    std::ofstream outFile("savegame.txt");
    if (outFile.is_open()) {
        // Lưu điểm số
        outFile << score << std::endl;
        // Lưu bảng
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                outFile << board[i][j] << " ";
            }
            outFile << std::endl;
        }
        outFile.close();
        std::cout << "Game saved successfully!" << std::endl;
    } else {
        std::cout << "Error: Unable to save game!" << std::endl;
    }
}

// Tải trạng thái trò chơi từ file, trả về true nếu thành công
bool loadGame() {
    std::ifstream inFile("savegame.txt");
    if (inFile.is_open()) {
        // Tải điểm số
        inFile >> score;
        // Tải bảng
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                inFile >> board[i][j];
            }
        }
        inFile.close();
        std::cout << "Game loaded successfully!" << std::endl;
        return true;
    } else {
        std::cout << "No saved game found. Starting new game..." << std::endl;
        return false;
    }
}