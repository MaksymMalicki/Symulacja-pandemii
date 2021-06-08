#pragma once
#include <vector>
#include "SickPerson.h"
#include "HealthyPerson.h"
#include "Disease.h"
#include "Vaccine.h"
#include "Board.h"
#include "QuarantineBoard.h"


class Controller {
private:
    vector<HealthyPerson> healthyPopulation;
    vector<SickPerson> sickPopulation;
    vector<SickPerson> quarantinePopulation;
    int healthyPopulationCount, sickPopulationCount, quarantinePopulationCount=0, deathCount=0;
    Board board;
    QuarantineBoard quarantineBoard;
    Disease disease;
    Vaccine vaccine;
    Texture texture1, texture2, texture3;
public:
    Controller(Board& brd, int healthyCount, int sickCount,
        /* Dane choroby*/ bool isMortal, int mortalityRate, int daysToInfected, bool resistantAfterInfection, int diseaseLength,
        /* Dane szczepionki */ bool createPossibility, int createDifficulty, int effectiveness, int vaccinesPerDay, int daysBeforeExpiry,
        /* Dane kwarantanny */ QuarantineBoard& quarantineboard);

    int getMatchingHealthyPersonIndex(vector<HealthyPerson> v, HealthyPerson p);

    void HealthyToSick(HealthyPerson person);

    int getMatchingSickPersonIndex(vector<SickPerson> v, SickPerson p);

    void SickToHealthy(SickPerson person);

    void populationMove();

    void infect();

    void recover();

    void vaccinate();

    void expirePopulationVaccine();

    void kill();

    void moveToQuarantine();

    void moveToBoard();

    bool checkEndingConditions();

    void simulate();
};

