#pragma once
#include <vector>
#include <iostream>
#include "Board.h"
#include "Person.h"
#include <utility>

using namespace std;

Person::Person(Board& brd, int st, Texture &tex) {
    board = brd;
    state = st;
    sprite.setTexture(tex);
    sprite.setScale(Vector2f(0.05, 0.05));

}

void Person::spawn(Board& board) {
    while (board.board[ycord][xcord] != 0) {
        xcord = rand() % board.width;
        ycord = rand() % board.height;
    }
    board.board[ycord][xcord] = state;
    sprite.setPosition(Vector2f(100+xcord * 50, 100+ycord * 50));
}

void Person::makeMove(Board& board) {
    int choice = rand() % 4 + 1;
    switch (choice) {
    case 1:
        if (ycord > 0 && board.board[ycord - 1][xcord] == 0) {
            board.board[ycord][xcord] = 0;
            board.board[ycord - 1][xcord] = state;
            ycord--;
            direction.first = 0;
            direction.second = -1;
        }
        else {
            direction.first = 0;
            direction.second = 0;
        }
        break;
    case 2:
        if (xcord < board.width - 1 && board.board[ycord][xcord + 1] == 0) {
            board.board[ycord][xcord] = 0;
            board.board[ycord][xcord + 1] = state;
            xcord++;
            direction.first = 1;
            direction.second = 0;
        }
        else {
            direction.first = 0;
            direction.second = 0;
        }
        break;
    case 3:
        if (ycord < board.height - 1 && board.board[ycord + 1][xcord] == 0) {
            board.board[ycord][xcord] = 0;
            board.board[ycord + 1][xcord] = state;
            ycord++;
            direction.first = 0;
            direction.second = 1;
        }
        else {
            direction.first = 0;
            direction.second = 0;
        }
        break;
    case 4:
        if (xcord > 0 && board.board[ycord][xcord - 1] == 0) {
            board.board[ycord][xcord] = 0;
            board.board[ycord][xcord - 1] = state;
            xcord--;
            direction.first = -1;
            direction.second = 0;
        }
        else {
            direction.first = 0;
            direction.second = 0;
        }
        break;
    }
}

void Person::moveSprite(int &framerate) {

    sprite.move(Vector2f(50.0 / framerate * direction.first, 50.0 / framerate * direction.second));
}
