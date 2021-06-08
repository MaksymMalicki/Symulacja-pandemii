#pragma once
class Disease {
private:
    bool isMortal;
    int mortalityRate;
    int daysToInfected;
    int diseaseLength;
    bool infectAgain;
    bool resistantAfterInfection;
    friend class Controller;
public:
    Disease();
    Disease(bool ismort, int mortrate, int daystoinf, bool infagain, int dislen);
};