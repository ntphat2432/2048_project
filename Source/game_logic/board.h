#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>
#include <ctime>
#include <string>

class Board {
private:
    static const int SIZE = 4;      // Kích thước bảng
    static const int WIN_VALUE = 2048;  // Giá trị để thắng
    int board[SIZE][SIZE];          // Bảng trò chơi
    int score;                      // Điểm số hiện tại
    int highScore;                  // Điểm cao nhất của người dùng hiện tại
    int prevBoard[SIZE][SIZE];      // Lưu trạng thái bảng trước đó
    int prevScore;                  // Lưu điểm số trước đó
    bool canUndo;                   // Cờ để kiểm tra xem có thể undo không
    std::string currentUser;        // Tên người dùng hiện tại

public:
    Board();                        // Constructor để khởi tạo trò chơi
    void setCurrentUser(const std::string& username);  // Đặt người dùng hiện tại
    std::string getCurrentUser() const;  // Lấy tên người dùng hiện tại
    bool login(const std::string& username, const std::string& password);  // Đăng nhập
    bool registerUser(const std::string& username, const std::string& password);  // Đăng ký
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
    void loadHighScore();           // Tải high score của người dùng hiện tại
    void saveHighScore();           // Lưu high score của người dùng hiện tại
    int getHighScore();             // Lấy high score
    void saveState();               // Lưu trạng thái trước khi di chuyển
    void undo();                    // Hoàn tác nước đi
    bool canUndoMove();             // Kiểm tra xem có thể undo không
};

#endif