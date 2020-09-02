#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>


std::vector<int> findNeighbours(std::vector<std::vector<int>> board, int x, int y) {
    std::vector<int> neighbours{};

    for (int i=-1; i <= 1; ++i) {
        for (int j=-1; j <= 1; ++j) {
            if (i != 0 || j != 0) {           
                try {
                    neighbours.push_back(board.at(x+i).at(y+j));
                }
                catch (std::out_of_range) {
                    //std::cout << "board[" << x+i << "][" << y+j << "] doesn't exists!" << "\n";
                }
            }
        }
    }

    return neighbours;
}

int isAlive(std::vector<int> neighbours, bool currentElementState) {
    int numOf1s = std::count(neighbours.cbegin(), neighbours.cend(), 1);

    int isAlive;
    // Game conditions
    if (currentElementState == 1 && numOf1s < 2) {
        isAlive = 0;
    }
    if (currentElementState == 1 && (numOf1s == 2 || numOf1s == 3)) {
        isAlive = 1;
    }
    if (currentElementState == 1 && numOf1s > 3) {
        isAlive = 0;
    }
    if (currentElementState == 0 && numOf1s == 3) {
        isAlive = 1;
    }
    return isAlive;
}

void drawBoard(std::vector<std::vector<int>> board) {
    for (auto row : board) {
        for (int column : row) {
            if (column)
                std::cout << "⬛";
            else
                std::cout << "⬜";
        }
        std::cout << std::endl;
    }
}

void gameEngine(std::vector<std::vector<int>> board, int rowSize, int columnSize) {
    std::vector<std::vector<int>> newBoard(rowSize, std::vector<int>(columnSize));
    
    for (int i{0}; i < board.size(); ++i) {
        for (int j{0}; j < board[i].size(); ++j) {
            std::vector<int> neighbours = findNeighbours(board, i, j);
            newBoard[i][j] = isAlive(neighbours, board[i][j]);
        }
    }

    drawBoard(newBoard);

    // Run game again
    usleep(1000000);
    gameEngine(newBoard, rowSize, columnSize);
}

int main() {
    const int rowSize = 30;
    const int columnSize = 60;
    // Auto initialize board with random 0s and 1s
    std::vector<std::vector<int>> board(rowSize, std::vector<int>(columnSize));
    srand(time(0));
    for (int i{0}; i < board.size(); ++i) {
        std::generate(board[i].begin(), board[i].end(), [](){
            return rand() % 2;
        });
    }
    std::cout << "Initialized board:" << std::endl;
    drawBoard(board);
    std::cout << "Press any key to start the game...";
    std::cin.ignore();
    std::cout << std::endl;
    gameEngine(board, rowSize, columnSize);
}
