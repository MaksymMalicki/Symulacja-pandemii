#include "Disease.h"


Disease::Disease() {
    isMortal = true;
    mortalityRate = 2;
    daysToInfected = 3;
    resistantAfterInfection = false;
    diseaseLength = 10;
}
Disease::Disease(bool ismort, int mortrate, int daystoinf, bool infagain, int dislen) {
    isMortal = ismort;
    mortalityRate = mortrate;
    daysToInfected = daystoinf;
    resistantAfterInfection = infagain;
    diseaseLength = dislen;
}
