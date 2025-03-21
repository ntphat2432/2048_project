#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>
#include <ctime>

const int SIZE = 4;
extern int board[SIZE][SIZE];

void printBoard();
void addRandomTile();
bool moveUp();
bool moveDown();
bool moveLeft();
bool moveRight();

#endif