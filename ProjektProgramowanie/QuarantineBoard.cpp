#include <iostream>
#include <vector>
#include "QuarantineBoard.h"
#include "Board.h"

using namespace std;

QuarantineBoard::QuarantineBoard() : Board() {
    width = 10;
    height = 1;
}

QuarantineBoard::QuarantineBoard(int w, int h) : Board(w, h) {
    width = w;
    height = h;
}

void QuarantineBoard::printBoard(int population) {
    if (population > 0) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 3) {
                    cout << char(219);
                }
            }
            cout << endl;
        }
    }
}

void QuarantineBoard::increaseSize(int& population) {
    if (board.size() == 0) {
        cout << "Creating quarantine board!" << endl;
        board.push_back(vector<int>());
    }
    if (population % width == 0) {
        board.push_back(vector<int>());
        height++;
    }
    else {
        cout << "Current quarantine board height is: " << height << endl;
        board[height-1].push_back(3);
    }
    cout << "Blob was moved to quarantine!" << endl;

}

void QuarantineBoard::decreaseSize(int& population) {
    if (board.size() > 0 && population>0) {
        if (population % width == 0) {
            board.erase(board.begin() + height);
            height--;
        }
        else {
            board[height - 1].erase(board[height - 1].begin() + (population % width));
        }
        cout << "Quarantine of blob is over!" << endl;
    }
}