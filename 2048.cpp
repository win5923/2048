#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int SIZE = 4;
const int WIN_VALUE = 2048;

class Game2048 {
private:
    vector<vector<int>> board;

    void addRandomTile() {
        vector<pair<int, int>> emptyCells;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == 0) {
                    emptyCells.emplace_back(i, j);
                }
            }
        }

        if (!emptyCells.empty()) {
            int index = rand() % emptyCells.size();
            int value = (rand() % 10 == 0) ? 4 : 2; // 10% chance of 4, 90% chance of 2
            board[emptyCells[index].first][emptyCells[index].second] = value;
        }
    }

    bool moveLeft() {
        bool moved = false;
        for (int i = 0; i < SIZE; ++i) {
            vector<int> row;
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] != 0) row.push_back(board[i][j]);
            }
            vector<int> newRow(SIZE, 0);
            int pos = 0;
            for (int j = 0; j < row.size(); ++j) {
                if (j + 1 < row.size() && row[j] == row[j + 1]) {
                    newRow[pos] = row[j] * 2;
                    moved = true;
                    ++j;
                } else {
                    newRow[pos] = row[j];
                }
                ++pos;
            }
            if (newRow != board[i]) moved = true;
            board[i] = newRow;
        }
        return moved;
    }

    void rotateBoard() {
        vector<vector<int>> newBoard(SIZE, vector<int>(SIZE, 0));
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                newBoard[j][SIZE - 1 - i] = board[i][j];
            }
        }
        board = newBoard;
    }

    bool moveInDirection(char direction) {
        bool moved = false;
        switch (direction) {
            case 's':
                rotateBoard();
                moved = moveLeft();
                rotateBoard();
                rotateBoard();
                rotateBoard();
                break;
            case 'w':
                rotateBoard();
                rotateBoard();
                rotateBoard();
                moved = moveLeft();
                rotateBoard();
                break;
            case 'a':
                moved = moveLeft();
                break;
            case 'd':
                rotateBoard();
                rotateBoard();
                moved = moveLeft();
                rotateBoard();
                rotateBoard();
                break;
        }
        return moved;
    }

    bool hasMoved() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == 0) return true;
                if (i > 0 && board[i][j] == board[i - 1][j]) return true;
                if (j > 0 && board[i][j] == board[i][j - 1]) return true;
            }
        }
        return false;
    }

    void printBoard() {
        for (const auto& row : board) {
            for (int cell : row) {
                cout << (cell == 0 ? "." : to_string(cell)) << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

public:
    Game2048() : board(SIZE, vector<int>(SIZE, 0)) {
        srand(time(0));
        addRandomTile();
        addRandomTile();
    }

    void play() {
        char command;
        while (true) {
            printBoard();
            cout << "Enter move (w/a/s/d): ";
            cin >> command;
            if (command == 'q') break;
            if (moveInDirection(command)) {
                addRandomTile();
                if (!hasMoved()) {
                    cout << "Game Over!" << endl;
                    break;
                }
            }
            if (any_of(board.begin(), board.end(), [](const vector<int>& row) {
                return find(row.begin(), row.end(), WIN_VALUE) != row.end();
            })) {
                cout << "You Win!" << endl;
                break;
            }
        }
    }
};

int main() {
    Game2048 game;
    game.play();
    return 0;
}
