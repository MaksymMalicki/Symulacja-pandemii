#pragma once
#include "Person.h"
#include "QuarantineBoard.h"

class SickPerson : public Person {
private:
    using Person::Person; // dziedziczy konstruktor rodzica, brak potrzeby tworzenia konstruktora dziecka
    int daysTillHealthy = 0;
    bool onQuarantine = false;
    friend class Controller;
    friend class QuarantineBoard;
    friend class Board;
public:
    
    void increaseDaysTillHealthy();
};