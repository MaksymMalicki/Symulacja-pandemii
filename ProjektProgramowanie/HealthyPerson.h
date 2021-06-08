#pragma once
#include "Person.h"
#include "Vaccine.h"



class HealthyPerson : public Person {
    using Person::Person; // dziedziczy konstruktor rodzica, brak potrzeby tworzenia konstruktora dziecka
private:
    int aroundSickDaysCount = 0;
    bool vaccinated = false;
    bool resistant = false;
    int vaccineDays = 0;
    friend class Controller;
public:
    bool checkConditions(Board& board, bool left, bool top_left, bool top, bool top_right, bool right, bool bottom_right, bool bottom, bool bottom_left);

    bool checkForSick(Board& board);

    void increaseDaysAroundSick();

    bool expireVaccine(Vaccine vac);
};