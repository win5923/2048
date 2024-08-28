#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

class Game2048 {
private:
    vector<vector<int>> board;
    int score;
    bool moved;
    // 0: down, 2: up
    vector<int> dirRow = {1, 0, -1, 0}; 
    // 1: right, 3: left
    vector<int> dirCol = {0, 1, 0, -1};

    void initializeBoard() {
        board = vector<vector<int>>(4, vector<int>(4, 0));
        score = 0;
        addRandomTile();
        addRandomTile();
    }
    

    void addRandomTile() {
        int occupied = 1, row, column;
        
        while(occupied) {
            row = rand() % 4;
            column = rand() % 4;
            if(board[row][column] == 0) occupied = 0;
        }
        board[row][column] = 2;
    }

    bool canMove(int i , int j, int nextI, int nextJ) {
        if(nextI < 0 || nextI >= 4 || nextJ < 0 || nextJ >= 4 || (board[i][j] != board[nextI][nextJ] && board[nextI][nextJ] != 0 )) return false;
        return true;
    }

    void printBoard() {
        // system("cls");
        system("clear");
        cout << "\nScore: " << score << endl;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (board[i][j] == 0) {
                    cout << setw(5) << ".";
                } else {
                    cout << setw(5) << board[i][j];
                }
            }
            cout << "\n";
        }
    }
    
    void applyMove(int direction) {
        int startRow = 0, startCol = 0, rowStep = 1, colStep = 1;
        
         vector<vector<bool>> merged(4, vector<bool>(4, false)); // check merge
    
        // if go up or go left
        if(direction == 0) {
            startRow = 3;
            rowStep = -1;
        }
        else if(direction == 1) {
            startCol = 3;
            colStep = -1;
        }
        
        do {
            moved = false;
            for(int i = startRow; i >= 0 && i < 4; i += rowStep) {
                for(int j = startCol; j >= 0 && j < 4; j += colStep) {
                    int nextI = i + dirRow[direction], nextJ = j + dirCol[direction];
                    if(board[i][j] && canMove(i, j, nextI, nextJ)) {
                        // cout << i << " " << j << " " << nextI<< " " << nextJ << endl;
                        if (board[nextI][nextJ] == board[i][j] && !merged[i][j]) {
                            board[nextI][nextJ] *= 2;
                            score += board[nextI][nextJ];
                            board[i][j] = 0;
                            merged[nextI][nextJ] = true;
                            moved = true;
                        } else if (board[nextI][nextJ] == 0) {
                            board[nextI][nextJ] = board[i][j];
                            board[i][j] = 0;
                            moved = true;
                        }
                    }
                }
            }
        } while(moved);
        
    }
    
    bool checkBoard() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (board[i][j] == 0) return true;
            }
        }
        return false;
    }


public:
    Game2048() {
        srand(time(0));
        initializeBoard();
    }

    void play() {
        char move;
        while (true) {
            printBoard();
            if(!checkBoard()) {
                cout << "Game Over! Final Score: " << score << endl;
                break;
            }
            
            int commandToDir;
            cout << "Enter move (w/a/s/d): ";
            cin >> move;

            if (move == 's') {
                commandToDir = 0;
            } else if (move == 'd') {
                commandToDir = 1;
            } else if (move == 'w') {
                commandToDir = 2;
            } else if (move == 'a') {
                commandToDir = 3;
            } else {
                cout << "Invalid move!" << endl;
                break;
            }
            
            applyMove(commandToDir);

            addRandomTile();
        }
    }
};

int main() {
    Game2048 game;
    game.play();
    return 0;
}
