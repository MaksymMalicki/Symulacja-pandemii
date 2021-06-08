#pragma once
#include <vector>

using namespace std;

class Board {
private:
    int width, height;
    vector<vector<int>> board;
    friend class Controller;
    friend class Person;
    friend class SickPerson;
    friend class HealthyPerson;
    friend class QuarantineBoard;
public:
    Board();

    Board(int width, int height);

    void createBoard();

    virtual void printBoard();
};