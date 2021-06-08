#pragma once

#include <vector>

#include "Board.h"
using namespace std;

class QuarantineBoard : public Board {
private:
    bool created = false;
    friend class Controller;
public:
    QuarantineBoard();

    QuarantineBoard(int w, int h);

    void printBoard(int population);

    void increaseSize(int& population);

    void decreaseSize(int& population);
};