#pragma once
#include "Person.h"
#include "HealthyPerson.h"
#include "Vaccine.h"
bool HealthyPerson::checkConditions(Board& board, bool left, bool top_left, bool top, bool top_right, bool right, bool bottom_right, bool bottom, bool bottom_left) {
    if (left) {
        if (board.board[ycord][xcord - 1] == 2) {
            return 1;
        }
    }
    if (top_left) {
        if (board.board[ycord - 1][xcord - 1] == 2) {
            return 1;
        }
    }
    if (top) {
        if (board.board[ycord - 1][xcord] == 2) {
            return 1;
        }
    }
    if (top_right) {
        if (board.board[ycord - 1][xcord + 1] == 2) {
            return 1;
        }
    }
    if (right) {
        if (board.board[ycord][xcord + 1] == 2) {
            return 1;
        }
    }
    if (bottom_right) {
        if (board.board[ycord + 1][xcord + 1] == 2) {
            return 1;
        }
    }
    if (bottom) {
        if (board.board[ycord + 1][xcord] == 2) {
            return 1;
        }
    }
    if (bottom_left) {
        if (board.board[ycord + 1][xcord - 1] == 2) {
            return 1;
        }
    }
    return 0;
}

bool HealthyPerson::checkForSick(Board& board) {
    if (xcord == 0 && ycord == 0) {
        return checkConditions(board, 0, 0, 0, 0, 1, 1, 1, 0);
    }
    if (ycord == 0 && xcord == board.width - 1) {
        return checkConditions(board, 1, 0, 0, 0, 0, 0, 1, 1);
    }
    if (ycord == board.height - 1 && xcord == board.width - 1) {
        return checkConditions(board, 1, 1, 1, 0, 0, 0, 0, 0);
    }
    if (ycord == board.height - 1 && xcord == 0) {
        return checkConditions(board, 0, 0, 1, 1, 1, 0, 0, 0);
    }
    if (xcord == 0) {
        return checkConditions(board, 0, 0, 1, 1, 1, 1, 1, 0);
    }
    if (ycord == 0) {
        return checkConditions(board, 1, 0, 0, 0, 1, 1, 1, 1);
    }
    if (xcord == board.width - 1) {
        return checkConditions(board, 1, 1, 1, 0, 0, 0, 1, 1);
    }
    if (ycord == board.height - 1) {
        return checkConditions(board, 1, 1, 1, 1, 1, 0, 0, 0);
    }
    else {
        return checkConditions(board, 1, 1, 1, 1, 1, 1, 1, 1);
    }
}

void HealthyPerson::increaseDaysAroundSick() {
    aroundSickDaysCount++;
}

bool HealthyPerson::expireVaccine(Vaccine vac) {
    if (vaccineDays < vac.daysBeforeExpiry) {
        vaccineDays++;
        return false;
    }
    else {
        cout << "Vaccine for blob at: " << xcord << " " << ycord << " expired!" << endl;
        vaccinated = false;
        return true;
    }
}

