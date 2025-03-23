#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <queue>
#include <ctime>

const int SIZE = 4;
int board[SIZE][SIZE] = {0};

// Thêm ô ngẫu nhiên
void addRandomTile() {
    int emptyCells = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) emptyCells++;
        }
    }
    if (emptyCells == 0) return;

    int pos = rand() % emptyCells;
    int count = 0;
    for (int i = 0; i < SIZE && count <= pos; i++) {
        for (int j = 0; j < SIZE && count <= pos; j++) {
            if (board[i][j] == 0) {
                if (count == pos) {
                    board[i][j] = (rand() % 2 == 0) ? 2 : 4;
                    return;
                }
                count++;
            }
        }
    }
}

// Di chuyển và hợp nhất dùng queue
void moveLeft() {
    for (int i = 0; i < SIZE; i++) {
        std::queue<int> q;
        // Đưa các ô không rỗng vào queue
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) q.push(board[i][j]);
            board[i][j] = 0;
        }
        // Hợp nhất các ô giống nhau
        int pos = 0;
        while (!q.empty()) {
            int val = q.front();
            q.pop();
            if (!q.empty() && q.front() == val) {
                board[i][pos++] = val * 2;
                q.pop();
            } else {
                board[i][pos++] = val;
            }
        }
    }
    addRandomTile();
}

void moveRight() {
    for (int i = 0; i < SIZE; i++) {
        std::queue<int> q;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) q.push(board[i][j]);
            board[i][j] = 0;
        }
        int pos = SIZE - 1;
        while (!q.empty()) {
            int val = q.front();
            q.pop();
            if (!q.empty() && q.front() == val) {
                board[i][pos--] = val * 2;
                q.pop();
            } else {
                board[i][pos--] = val;
            }
        }
    }
    addRandomTile();
}

void moveUp() {
    for (int j = 0; j < SIZE; j++) {
        std::queue<int> q;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] != 0) q.push(board[i][j]);
            board[i][j] = 0;
        }
        int pos = 0;
        while (!q.empty()) {
            int val = q.front();
            q.pop();
            if (!q.empty() && q.front() == val) {
                board[pos++][j] = val * 2;
                q.pop();
            } else {
                board[pos++][j] = val;
            }
        }
    }
    addRandomTile();
}

void moveDown() {
    for (int j = 0; j < SIZE; j++) {
        std::queue<int> q;
        for (int i = SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) q.push(board[i][j]);
            board[i][j] = 0;
        }
        int pos = SIZE - 1;
        while (!q.empty()) {
            int val = q.front();
            q.pop();
            if (!q.empty() && q.front() == val) {
                board[pos--][j] = val * 2;
                q.pop();
            } else {
                board[pos--][j] = val;
            }
        }
    }
    addRandomTile();
}

// Kiểm tra trạng thái game dùng BFS
bool checkGameState(int& result) {
    // Kiểm tra thắng (có ô 2048)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 2048) {
                result = 1; // Thắng
                return true;
            }
        }
    }

    // Kiểm tra thua (không còn nước đi)
    int emptyCells = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) emptyCells++;
            else if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return false;
            else if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return false;
        }
    }
    if (emptyCells > 0) return false; // Còn ô trống, chưa thua
    result = -1; // Thua
    return true;
}

// Vẽ bảng với SFML
void drawBoard(sf::RenderWindow& window, sf::Font& font) {
    window.clear(sf::Color(187, 173, 160)); // Màu nền
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            sf::RectangleShape tile(sf::Vector2f(90, 90));
            tile.setPosition(10 + j * 100, 10 + i * 100);
            tile.setFillColor(sf::Color(205, 193, 180));
            tile.setOutlineThickness(5);
            tile.setOutlineColor(sf::Color(187, 173, 160));

            if (board[i][j] != 0) {
                sf::Text number(std::to_string(board[i][j]), font, 30);
                number.setFillColor(sf::Color::Black);
                number.setPosition(40 + j * 100, 35 + i * 100);
                window.draw(number);
            }
            window.draw(tile);
        }
    }
    window.display();
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    sf::RenderWindow window(sf::VideoMode(400, 400), "2048 Game");
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "Error loading font\n";
        return -1;
    }

    // Khởi tạo game
    addRandomTile();
    addRandomTile();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) moveLeft();
                else if (event.key.code == sf::Keyboard::Right) moveRight();
                else if (event.key.code == sf::Keyboard::Up) moveUp();
                else if (event.key.code == sf::Keyboard::Down) moveDown();
            }
        }

        int gameResult = 0;
        if (checkGameState(gameResult)) {
            std::cout << (gameResult == 1 ? "You Win!\n" : "Game Over!\n");
            window.close();
        }

        drawBoard(window, font);
    }
    return 0;
}
