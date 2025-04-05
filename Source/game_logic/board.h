#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>
#include <ctime>

class Board {
private:
    static const int SIZE = 4;      // Kích thước bảng
    static const int WIN_VALUE = 2048;  // Giá trị để thắng
    int board[SIZE][SIZE];          // Bảng trò chơi
    int score;                      // Điểm số hiện tại
    int highScore;                  // Điểm cao nhất
    int prevBoard[SIZE][SIZE];      // Lưu trạng thái bảng trước đó
    int prevScore;                  // Lưu điểm số trước đó
    bool canUndo;                   // Cờ để kiểm tra xem có thể undo không

public:
    Board();                        // Constructor để khởi tạo trò chơi
    void printBoard();              // In bảng
    void addRandomTile();           // Thêm ô ngẫu nhiên
    bool moveUp();                  // Di chuyển lên
    bool moveDown();                // Di chuyển xuống
    bool moveLeft();                // Di chuyển trái
    bool moveRight();               // Di chuyển phải
    bool checkWin();                // Kiểm tra thắng
    bool checkLose();               // Kiểm tra thua
    int getScore();                 // Lấy điểm số hiện tại
    void saveGame();                // Lưu trò chơi
    bool loadGame();                // Tải trò chơi
    void loadHighScore();           // Tải high score
    void saveHighScore();           // Lưu high score
    int getHighScore();             // Lấy high score
    void saveState();               // Lưu trạng thái trước khi di chuyển
    void undo();                    // Hoàn tác nước đi
    bool canUndoMove();             // Kiểm tra xem có thể undo không
};

#endif