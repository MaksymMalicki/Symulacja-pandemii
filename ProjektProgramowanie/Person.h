#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Board.h"

using namespace sf;
using namespace std;

class Person {
protected:
    int xcord = 0, ycord = 0;
    int state;
    pair<int, int> direction = { 0,0 };
    Sprite sprite;
    Board board;
public:
    Person(Board& brd, int st, Texture &text);

    void spawn(Board& board);

    void makeMove(Board& board);

    void moveSprite(int &framerate);

};