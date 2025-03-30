#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>
#include <ctime>

const int SIZE = 4;
const int WIN_VALUE = 2048;
extern int board[SIZE][SIZE];
extern int score;  // Biến lưu điểm số

void printBoard();
void addRandomTile();
bool moveUp();
bool moveDown();
bool moveLeft();
bool moveRight();
bool checkWin();
bool checkLose();
int getScore();  // Hàm lấy điểm số
void saveGame();  // Lưu trạng thái trò chơi
bool loadGame();  // Tải trạng thái trò chơi, trả về true nếu thành công
void loadHighScore();  // Tải high score từ file
void saveHighScore();  // Lưu high score vào file
int getHighScore();    // Trả về high score

#endif