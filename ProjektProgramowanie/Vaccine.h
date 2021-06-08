#pragma once
#include <iostream>

using namespace std;

class Vaccine {
private:
    bool createPossibility;
    int createDifficulty;
    int effectiveness;
    int daysBeforeExpiry;
    int vaccinesPerDay;
    int daysCount = 0;
    bool created = false;
    friend class Controller;
    friend class HealthyPerson;
public:
    Vaccine();

    Vaccine(bool createpos, int creatediff, int effect, int vacperday, int dbf);

    void increaseVaccineDaysCount();
};
