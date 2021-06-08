#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <utility>

using namespace sf;
using namespace std;
#include "Board.h"
#include "Controller.h"
#include "QuarantineBoard.h"


int main()
{
    srand(time(NULL));
    int width=10, height=10, healthyCount = 0, sickCount = 0, mortalityRate = 0, daysToInfected = 0, diseaseLength = 0, createDifficulty = 0, effectiveness = 0, vaccinesPerDay = 0, daysBeforeExpiry = 0;
    bool isMortal, resistantAfterInfection, createPossibility;

    /*while (width > 20 || width<1) {
        system("cls");
        cout << "Podaj szerokosc planszy (1-20): " << endl;
        cin >> width;
    }
    while (height > 20 || height < 1) {
        system("cls");
        cout << "Podaj wysokosc planszy (1-20): " << endl;
        cin >> height;
    }
    while (healthyCount > ((height * width / 2) - 1) || healthyCount<1) {
        system("cls");
        cout << "Podaj poczatkowa ilosc osob zdrowych (1-"+ to_string(((height * width / 2) - 1))+": " << endl;
        cin >> healthyCount;
    }
    while ((sickCount + healthyCount) > (height * width / 2) || sickCount<1) {
        system("cls");
        cout << "Podaj poczatkowa ilosc osob chorych (1-" + to_string((height * width / 2)-healthyCount) + ": " << endl;
        cin >> sickCount;
    }
    string odpowiedz = "";
    while (odpowiedz != "TAK" && odpowiedz != "NIE") {
        system("cls");
        cout << "Podaj, czy choroba jest smiertelna (TAK/NIE): " << endl;
        cin >> odpowiedz;
    }
    if (odpowiedz == "TAK") {
        isMortal = true;
    }
    else {
        isMortal = false;
    }
    while ((mortalityRate < 1 || mortalityRate > 101)) {
        system("cls");
        cout << "Podaj umieralnosc (1-100) " << endl;
        cin >> mortalityRate;
    }
    while ((daysToInfected < 1 || daysToInfected > 31)) {
        system("cls");
        cout << "Podaj czas, po ktorym osoba sie zaraza (1-30) " << endl;
        cin >> daysToInfected;
    }
    odpowiedz = "";
    while (odpowiedz!="TAK" && odpowiedz!="NIE") {
        system("cls");
        cout << "Podaj, czy osoba ponownie moze sie zarazic (TAK/NIE): " << endl;
        cin >> odpowiedz;
    }
    if (odpowiedz == "TAK") {
        resistantAfterInfection = true;
    }
    else {
        resistantAfterInfection = false;
    }
    while ((diseaseLength < 1 || diseaseLength > 31)) {
        system("cls");
        cout << "Podaj dlugosc trwania choroby (1-30) " << endl;
        cin >> diseaseLength;
    }
    odpowiedz = "";
    while (odpowiedz != "TAK" && odpowiedz != "NIE") {
        system("cls");
        cout << "Podaj, czy mozna stworzyc szczepionke (TAK/NIE):  " << endl;
        cin >> odpowiedz;
    }
    if (odpowiedz == "TAK") {
        createPossibility = true;
    }
    else {
        createPossibility = false;
    }
    while ((createDifficulty < 1 || createDifficulty > 6)) {
        system("cls");
        cout << "Podaj trudnosc utworzenia szczepionki (1-5) " << endl;
        cin >> createDifficulty;
    }
    while ((effectiveness < 1 || effectiveness > 100)) {
        system("cls");
        cout << "Podaj skuteczność szczepionki (1-100) " << endl;
        cin >> effectiveness;
    }
    while ((vaccinesPerDay < 1 || vaccinesPerDay > 5)) {
        system("cls");
        cout << "Podaj dzienna ilosc osob do zaszczepienia (1-5) " << endl;
        cin >> vaccinesPerDay;
    }
    while ((daysBeforeExpiry < 1 || daysBeforeExpiry > 31)) {
        system("cls");
        cout << "Podaj, po ilu dniach szczepionka przestaje dzialac (1-30) " << endl;
        cin >> daysBeforeExpiry;
    }*/



    
    Board board(width, height);/*
    board.setSize(width, height);
    board.createBoard();
    QuarantineBoard quarantineBoard(board.width);
    Controller controller(board, healthyCount, sickCount, isMortal, mortalityRate, daysToInfected, resistantAfterInfection, diseaseLength, createPossibility, createDifficulty, effectiveness, vaccinesPerDay, daysBeforeExpiry, quarantineBoard);
    */
    board.createBoard();
    QuarantineBoard quarantineBoard(10, 1);
    Controller controller(board, 25, 25, true, 5, 3, true, 14, true, 2, 70, 2, 14, quarantineBoard);
    controller.simulate();
    
    return 0;
}


