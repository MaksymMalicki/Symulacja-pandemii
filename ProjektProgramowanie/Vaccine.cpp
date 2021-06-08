#pragma once
#include <iostream>
#include "Vaccine.h";
using namespace std;


Vaccine::Vaccine() {
    createPossibility = true;
    createDifficulty = 10;
    effectiveness = 50;
    vaccinesPerDay = 2;
    daysBeforeExpiry = 14;
}

Vaccine::Vaccine(bool createpos, int creatediff, int effect, int vacperday, int dbf) {
    createPossibility = createpos;
    createDifficulty = creatediff;
    effectiveness = effect;
    vaccinesPerDay = vacperday;
    daysBeforeExpiry = dbf;
}

void Vaccine::increaseVaccineDaysCount() {
    daysCount++;
    cout << "Vaccine: " << daysCount << "/" << 10 * createDifficulty << endl;
    if (daysCount >= 10 * createDifficulty) {
        created = true;
    }
}

