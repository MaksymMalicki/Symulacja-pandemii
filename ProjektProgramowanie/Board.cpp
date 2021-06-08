#include <iostream>
#include <vector>
#include "Board.h"

using namespace std;

Board::Board() {
    width = 10;
    height = 10;
}
Board::Board(int w, int h) {
    width = w;
    height = h;
}

void Board::createBoard() {
    vector<vector<int>> vec(height, vector<int>(width, 0));
    board = vec;
}

void Board::printBoard() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (board[i][j] == 1) {
                cout << char(219);
            }
            else if (board[i][j] == 2) {
                cout << "#";
            }
            else {
                cout << "0";
            }
        }
        cout << endl;
    }
    cout << endl;
}