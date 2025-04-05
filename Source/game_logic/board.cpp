#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "board.h"

// Constructor: Khởi tạo bảng, điểm số, high score, và trạng thái undo
Board::Board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
            prevBoard[i][j] = 0;
        }
    }
    score = 0;
    highScore = 0;
    prevScore = 0;
    canUndo = false;
    currentUser = "";  // Khởi tạo người dùng hiện tại
}

// Đặt người dùng hiện tại
void Board::setCurrentUser(const std::string& username) {
    currentUser = username;
}

// Lấy tên người dùng hiện tại
std::string Board::getCurrentUser() const {
    return currentUser;
}

// Đăng nhập: Kiểm tra tên đăng nhập và mật khẩu
bool Board::login(const std::string& username, const std::string& password) {
    std::ifstream inFile("users.txt");
    std::string storedUsername, storedPassword;
    int storedHighScore;

    if (inFile.is_open()) {
        while (inFile >> storedUsername >> storedPassword >> storedHighScore) {
            if (storedUsername == username && storedPassword == password) {
                currentUser = username;
                highScore = storedHighScore;
                inFile.close();
                return true;
            }
        }
        inFile.close();
    }
    return false;
}

// Đăng ký: Thêm người dùng mới vào file
bool Board::registerUser(const std::string& username, const std::string& password) {
    // Kiểm tra xem tên đăng nhập đã tồn tại chưa
    std::ifstream inFile("users.txt");
    std::string storedUsername, storedPassword;
    int storedHighScore;

    if (inFile.is_open()) {
        while (inFile >> storedUsername >> storedPassword >> storedHighScore) {
            if (storedUsername == username) {
                inFile.close();
                return false;  // Tên đăng nhập đã tồn tại
            }
        }
        inFile.close();
    }

    // Thêm người dùng mới
    std::ofstream outFile("users.txt", std::ios::app);  // Mở file ở chế độ append
    if (outFile.is_open()) {
        outFile << username << " " << password << " " << 0 << std::endl;  // High score ban đầu là 0
        outFile.close();
        currentUser = username;
        highScore = 0;
        return true;
    }
    return false;
}


// In bảng 4x4 ra console, thay số 0 bằng dấu chấm và căn chỉnh ô
void Board::printBoard() {
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
void Board::addRandomTile() {
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
bool Board::moveLeft() {
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
bool Board::moveRight() {
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
bool Board::moveUp() {
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
bool Board::moveDown() {
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
bool Board::checkWin() {
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
bool Board::checkLose() {
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
int Board::getScore() {
    return score;
}

// Lưu trạng thái trò chơi (bảng và điểm số) vào file
void Board::saveGame() {
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
    canUndo = false;  // Sau khi lưu, không cho phép undo
}

// Tải trạng thái trò chơi từ file, trả về true nếu thành công
bool Board::loadGame() {
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
        canUndo = false;  // Sau khi tải, không cho phép undo
        return true;
    } else {
        std::cout << "No saved game found. Starting new game..." << std::endl;
        return false;
    }
}

// Tải high score của người dùng hiện tại
void Board::loadHighScore() {
    if (currentUser.empty()) return;

    std::ifstream inFile("users.txt");
    std::string username, password;
    int storedHighScore;

    if (inFile.is_open()) {
        while (inFile >> username >> password >> storedHighScore) {
            if (username == currentUser) {
                highScore = storedHighScore;
                break;
            }
        }
        inFile.close();
    }
}

// Lưu high score của người dùng hiện tại
void Board::saveHighScore() {
    if (currentUser.empty()) return;

    if (score > highScore) {
        highScore = score;
    }

    // Đọc tất cả dữ liệu từ file
    std::ifstream inFile("users.txt");
    std::stringstream buffer;
    std::string username, password;
    int storedHighScore;
    bool updated = false;

    if (inFile.is_open()) {
        while (inFile >> username >> password >> storedHighScore) {
            if (username == currentUser) {
                buffer << username << " " << password << " " << highScore << std::endl;
                updated = true;
            } else {
                buffer << username << " " << password << " " << storedHighScore << std::endl;
            }
        }
        inFile.close();
    }

    // Ghi lại dữ liệu vào file
    std::ofstream outFile("users.txt");
    if (outFile.is_open()) {
        outFile << buffer.str();
        outFile.close();
    }
}

// Trả về high score
int Board::getHighScore() {
    return highScore;
}

// Lưu trạng thái hiện tại của bảng và điểm số trước khi di chuyển
void Board::saveState() {
    // Sao chép bảng hiện tại vào prevBoard
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            prevBoard[i][j] = board[i][j];
        }
    }
    // Sao chép điểm số hiện tại vào prevScore
    prevScore = score;
    canUndo = true;  // Cho phép undo sau khi lưu trạng thái
}

// Hoàn tác nước đi: khôi phục bảng và điểm số từ trạng thái trước đó
void Board::undo() {
    if (!canUndo) {
        std::cout << "Cannot undo!" << std::endl;
        return;
    }
    // Khôi phục bảng
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = prevBoard[i][j];
        }
    }
    // Khôi phục điểm số
    score = prevScore;
    canUndo = false;  // Sau khi undo, không cho phép undo tiếp
}

// Kiểm tra xem có thể undo không
bool Board::canUndoMove() {
    return canUndo;
}