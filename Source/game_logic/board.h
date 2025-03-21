#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>
#include <ctime>

const int SIZE = 4;
const int WIN_VALUE = 2048;  // Giá trị để thắng
extern int board[SIZE][SIZE];

void printBoard();
void addRandomTile();
bool moveUp();
bool moveDown();
bool moveLeft();
bool moveRight();
bool checkWin();  // Kiểm tra thắng
bool checkLose(); // Kiểm tra thua

#endif