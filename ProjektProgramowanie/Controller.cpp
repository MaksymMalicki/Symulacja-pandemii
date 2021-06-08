#include <SFML/Graphics.hpp>
#include "Controller.h"
#include <Windows.h>
#include <string>

using namespace sf;

Controller::Controller(Board& brd, int healthyCount, int sickCount,
    /* Dane choroby*/ bool isMortal, int mortalityRate, int daysToInfected, bool resistantAfterInfection, int diseaseLength,
    /* Dane szczepionki */ bool createPossibility, int createDifficulty, int effectiveness, int vaccinesPerDay, int daysBeforeExpiry,
    /* Dane kwarantanny */ QuarantineBoard& quarantineboard) {
    healthyPopulationCount = healthyCount;
    sickPopulationCount = sickCount;
    board = brd;
    quarantineBoard = quarantineboard;
    disease = Disease(isMortal, mortalityRate, daysToInfected, resistantAfterInfection, diseaseLength);
    if (createPossibility) {
        vaccine = Vaccine(createPossibility, createDifficulty, effectiveness, vaccinesPerDay, daysBeforeExpiry);
    }
    if (!texture1.loadFromFile("sprites/zielony.png")) {
        cout << "Nie udalo sie zaladowac tekstury" << endl;
        system("pause");
    }
    if (!texture2.loadFromFile("sprites/czerwony.png")) {
        cout << "Nie udalo sie zaladowac tekstury" << endl;
        system("pause");
    }
    if (!texture3.loadFromFile("sprites/niebieski.png")) {
        cout << "Nie udalo sie zaladowac tekstury" << endl;
        system("pause");
    }
    for (int i = 0; i < healthyPopulationCount; i++) {
        healthyPopulation.push_back(HealthyPerson(board, 1, texture1));
        healthyPopulation[i].spawn(board);
    }
    for (int i = 0; i < sickPopulationCount; i++) {
        sickPopulation.push_back(SickPerson(board, 2, texture2));
        sickPopulation[i].spawn(board);
    }
}

int Controller::getMatchingHealthyPersonIndex(vector<HealthyPerson> v, HealthyPerson p) {

    for (int i = 0; i < healthyPopulationCount; i++) {
        if (v[i].xcord == p.xcord && v[i].ycord == p.ycord && v[i].state == p.state) {
            return i;
        }
    }
    return -1;

}

void Controller::HealthyToSick(HealthyPerson person) {
    int index = getMatchingHealthyPersonIndex(healthyPopulation, person);
    if (index) {
        SickPerson new_sick_person(board, 2, texture2);
        new_sick_person.xcord = healthyPopulation[index].xcord;
        new_sick_person.ycord = healthyPopulation[index].ycord;
        board.board[new_sick_person.ycord][new_sick_person.xcord] = new_sick_person.state;
        healthyPopulation.erase(healthyPopulation.begin() + index);
        sickPopulation.push_back(new_sick_person);
        healthyPopulationCount--;
        sickPopulationCount++;
        sickPopulation[sickPopulationCount - 1].spawn(board);
    }
}

int Controller::getMatchingSickPersonIndex(vector<SickPerson> v, SickPerson p) {

    for (int i = 0; i < sickPopulationCount; i++) {
        if (v[i].xcord == p.xcord && v[i].ycord == p.ycord && v[i].state == p.state) {
            return i;
        }
    }
    return -1;

}

void Controller::SickToHealthy(SickPerson person) {
    int index = getMatchingSickPersonIndex(sickPopulation, person);
    if (index) {
        HealthyPerson new_healthy_person(board, 1, texture1);
        new_healthy_person.xcord = sickPopulation[index].xcord;
        new_healthy_person.ycord = sickPopulation[index].ycord;
        board.board[new_healthy_person.ycord][new_healthy_person.xcord] = new_healthy_person.state;
        sickPopulation.erase(sickPopulation.begin() + index);
        healthyPopulation.push_back(new_healthy_person);
        sickPopulationCount--;
        healthyPopulationCount++;
        healthyPopulation[healthyPopulationCount - 1].spawn(board);
    }
}

void Controller::populationMove() { //funkcja odpowiedzialna za poruszanie cala populacja

    cout << "Population move turn: " << endl;
    if (healthyPopulationCount > 0) {
        for (int j = 0; j < healthyPopulationCount; j++) {
            healthyPopulation[j].makeMove(board);
            cout << "healthy: " << healthyPopulation[j].xcord << " " << healthyPopulation[j].ycord << endl;
        }
        for (int j = 0; j < sickPopulationCount; j++) {
            sickPopulation[j].makeMove(board);
            cout << "sick: " << sickPopulation[j].xcord << " " << sickPopulation[j].ycord << endl;
        }
    }
}

void Controller::infect() { // funkcja odpowiedzialna za iterowanie po jednostkach zdrowych i sprawdzanie czy spelniaja warunki zarazenia; jesli tak, zaraz
    cout << "Infection turn: " << endl;
    if (healthyPopulationCount > 0) {
        for (int i = 0; i < healthyPopulationCount; i++) {
            if (!healthyPopulation[i].vaccinated) {
                if (healthyPopulation[i].checkForSick(board)) {
                    healthyPopulation[i].increaseDaysAroundSick();
                    cout << "blob at (not vaccinated): " << healthyPopulation[i].xcord << " " << healthyPopulation[i].ycord << " spent 1 day nearby sick; days count:" << healthyPopulation[i].aroundSickDaysCount << endl;

                }
                if (healthyPopulation[i].aroundSickDaysCount == disease.daysToInfected) {
                    cout << "blob at (not vaccinated): " << healthyPopulation[i].xcord << " " << healthyPopulation[i].ycord << " turned sick" << endl;
                    HealthyToSick(healthyPopulation[i]);
                }
            }
            else {
                cout << "blob at " << healthyPopulation[i].xcord << " " << healthyPopulation[i].ycord << " is safely vaccinated" << endl;
            }
        }
    }
}

void Controller::recover() { //funkcja odpowiedzialna za iterowanie po jednostkach chorych i sprawdzanie czy jest chory wystarczaj¹co dlugo; jesli tak, wyzdrowiej; jeœli nie zwieksz iloœæ chorych dni o 1
    cout << "Recovery turn: " << endl;
    if (sickPopulationCount > 0) {
        for (int i = 0; i < sickPopulationCount; i++) {
            if (sickPopulation[i].daysTillHealthy == disease.diseaseLength) {
                cout << "blob at: " << sickPopulation[i].xcord << " " << sickPopulation[i].ycord << " turned healhy" << endl;
                SickToHealthy(sickPopulation[i]);
            }
            else {
                sickPopulation[i].increaseDaysTillHealthy();
            }

        }
    }
}

void Controller::vaccinate() {
    cout << "Vaccination turn: " << endl;
    if (healthyPopulationCount > 0 && healthyPopulationCount > vaccine.vaccinesPerDay) {
        for (int i = 0; i < vaccine.vaccinesPerDay; i++) {
            int index = rand() % healthyPopulationCount;
            int iter = 0;
            while (healthyPopulation[index].vaccinated == true && iter < vaccine.vaccinesPerDay) {
                index = rand() % healthyPopulationCount;
                iter++;
            }
            if (rand() % 100 + 1 <= vaccine.effectiveness) {
                healthyPopulation[index].vaccinated = true;
                cout << "blob at: " << healthyPopulation[index].xcord << " " << healthyPopulation[index].ycord << " got vaccinated!" << endl;
                healthyPopulation[index].sprite.setTexture(texture3);
            }
        }
    }
}

void Controller::expirePopulationVaccine() {
    cout << "Vaccine expiry turn: " << endl;
    if (healthyPopulationCount > 0) {
        for (int i = 0; i < healthyPopulationCount; i++) {
            if (healthyPopulation[i].expireVaccine(vaccine)) {
                healthyPopulation[i].sprite.setTexture(texture3);
            }
        }
    }
}



void Controller::kill() {
    cout << "Kill turn: " << endl;    
    if (disease.isMortal) {
        int deathChance = 0;
        if (sickPopulationCount) {
            for (int i = 0; i < sickPopulationCount; i++) {
                deathChance = rand() % 100;
                cout << "deathChance: " << deathChance << " mortalityRate: " << disease.mortalityRate << endl;
                if (deathChance < disease.mortalityRate) {
                    cout << "blob at: " << sickPopulation[i].xcord << " " << sickPopulation[i].ycord << " died" << endl;
                    board.board[sickPopulation[i].ycord][sickPopulation[i].xcord] = 0;
                    sickPopulation.erase(sickPopulation.begin() + i);
                    sickPopulationCount--;
                    deathCount++;
                }
            }
        }
    }
}

void Controller::moveToQuarantine() {
    cout << "Move to quarantine turn: " << endl;
    if (sickPopulationCount > 0) {
        int index = rand() % sickPopulationCount;
        int moveChance = rand() % 4;
        if (moveChance < 1) {
            SickPerson person = sickPopulation[index];
            board.board[person.ycord][person.xcord] = 0;
            sickPopulation.erase(sickPopulation.begin() + index);
            sickPopulationCount--;
            quarantinePopulation.push_back(person);
            quarantinePopulationCount++;
            quarantineBoard.increaseSize(quarantinePopulationCount);
            cout << "days till healthy: " << person.daysTillHealthy << endl;
        }
    }
}

void Controller::moveToBoard() {
    cout << "Move back to board turn: " << endl;
    if (quarantinePopulationCount > 0) {
        for (int i = 0; i < quarantinePopulationCount; i++) {
            if (quarantinePopulation[i].daysTillHealthy == disease.diseaseLength) {
                quarantinePopulation.erase(quarantinePopulation.begin() + i);
                quarantinePopulationCount--;
                healthyPopulationCount++;
                HealthyPerson person(board, 1, texture1);
                healthyPopulation.push_back(person);
                healthyPopulation[healthyPopulationCount - 1].spawn(board);
                cout << "Healthy blob was removed from quarantine board and spawned at: " << healthyPopulation[healthyPopulationCount - 1].xcord << " " << healthyPopulation[healthyPopulationCount - 1].xcord << endl;
                quarantineBoard.decreaseSize(quarantinePopulationCount);
                
            }
            else {
                quarantinePopulation[i].increaseDaysTillHealthy();
            }
        }
    }
}

bool Controller::checkEndingConditions() {
    if (sickPopulationCount == 0 || healthyPopulationCount == 0) {
        return 1;
    }
    return 0;
}

void Controller::simulate() {
    //Tworzenie okna
    RenderWindow window(VideoMode(1980, 1080), "Symulacja pandemii");
    window.setFramerateLimit(60);
    int framerate = 30;
    int frames = 0;
    int days=0;
    //Tworzenie liczników
    Text sick_counter, healthy_counter, quarantine_counter, death_counter;
    Font font;
    int offset = 150;
    if (!font.loadFromFile("Raleway.ttf")) {
        cout << "Nie udalo zaladowac sie czcionki!" << endl;
        system("pause");
    }
    Text header1;
    header1.setFont(font);
    header1.setPosition(Vector2f(140 + board.width * 50, 100));
    header1.setFillColor(Color(255, 255, 255));
    header1.setCharacterSize(40);
    header1.setString("Liczniki: ");

    sick_counter.setFont(font);
    sick_counter.setPosition(Vector2f(140+board.width*50, 100+50));
    sick_counter.setFillColor(Color(255, 255, 255));
    sick_counter.setCharacterSize(30);

    healthy_counter.setFont(font);
    healthy_counter.setPosition(Vector2f(140 + board.width * 50, 100 + 2*50));
    healthy_counter.setFillColor(Color(255, 255, 255));
    healthy_counter.setCharacterSize(30);

    quarantine_counter.setFont(font);
    quarantine_counter.setPosition(Vector2f(140 + board.width * 50, 100 + 3*50));
    quarantine_counter.setFillColor(Color(255, 255, 255));
    quarantine_counter.setCharacterSize(30);

    death_counter.setFont(font);
    death_counter.setPosition(Vector2f(140 + board.width * 50, 100 + 4*50));
    death_counter.setFillColor(Color(255, 255, 255));
    death_counter.setCharacterSize(30);

    //Obramówka g³ównej planszy
    RectangleShape rect(Vector2f(50*board.width, 50*board.height));
    rect.setFillColor(Color(0, 0, 0));
    rect.setOutlineColor(Color(255, 255, 255));
    rect.setOutlineThickness(1);
    rect.setPosition(Vector2f(100, 100));

    //Obramówka planszy kwarantanny
    RectangleShape quarantine_rect(Vector2f(50 * quarantineBoard.width, 50));
    quarantine_rect.setFillColor(Color(0, 0, 0));
    quarantine_rect.setOutlineColor(Color(255, 255, 255));
    quarantine_rect.setOutlineThickness(1);
    quarantine_rect.setPosition(Vector2f(100, 100+board.height*50+50));

    //Tekstura bloba na kwarantannie
    Texture quarantine_person_texture;
    if (!quarantine_person_texture.loadFromFile("sprites/pomarancz.png")) {
        cout << "Nie udalo sie zaladowac tekstury" << endl;
        system("pause");
    }
    Sprite quarantine_person;
    quarantine_person.setTexture(quarantine_person_texture);
    quarantine_person.setScale(Vector2f(0.05, 0.05));

    //Dane choroby
    Text header2;
    header2.setFont(font);
    header2.setPosition(Vector2f(140 + board.width * 50, 100 + 6*50));
    header2.setFillColor(Color(255, 255, 255));
    header2.setCharacterSize(40);
    header2.setString("Dane choroby: ");

    Text data1;
    data1.setFont(font);
    data1.setPosition(Vector2f(140 + board.width * 50, 100 + 7*50));
    data1.setFillColor(Color(255, 255, 255));
    data1.setCharacterSize(30);
    data1.setString("Smiertelna: " + to_string(disease.isMortal) + "   Smiertelnosc: " + to_string(disease.mortalityRate) + "/100   Dni do zarazenia: " + to_string(disease.daysToInfected));
    
    Text data2;
    data2.setFont(font);
    data2.setPosition(Vector2f(140 + board.width * 50, 100 + 8*50));
    data2.setFillColor(Color(255, 255, 255));
    data2.setCharacterSize(30);
    data2.setString("Odpornosc po przebyciu choroby: " + to_string(disease.resistantAfterInfection) + "   Dlugosc choroby: " + to_string(disease.diseaseLength));

    //SZCZEPIONKA

    Text header3;
    header3.setFont(font);
    header3.setPosition(Vector2f(140 + board.width * 50, 100 + 9 * 50));
    header3.setFillColor(Color(255, 255, 255));
    header3.setCharacterSize(40);
    header3.setString("Postep szczepionki: ");

    Text data3;
    data3.setFont(font);
    data3.setPosition(Vector2f(140 + board.width * 50, 100 + 10 * 50));
    data3.setFillColor(Color(255, 255, 255));
    data3.setCharacterSize(30);
    data3.setString("Stworzona!");

    Text data4;
    data4.setFont(font);
    data4.setPosition(Vector2f(140 + board.width * 50, 100 + 10 * 50));
    data4.setFillColor(Color(255, 255, 255));
    data4.setCharacterSize(30);
    data4.setString("Mozliwa do stworzenia: " + to_string(vaccine.createPossibility) + "   Trudnosc stworzenia: " + to_string(vaccine.createDifficulty) + "/10   Skutecznosc: " + to_string(vaccine.effectiveness)+ "/100");

    Text data5;
    data5.setFont(font);
    data5.setPosition(Vector2f(140 + board.width * 50, 100 + 11 * 50));
    data5.setFillColor(Color(255, 255, 255));
    data5.setCharacterSize(30);
    data5.setString("Czas dzialania szczepionki: " + to_string(vaccine.daysBeforeExpiry) + "   Szczepionki dziennie: " + to_string(vaccine.vaccinesPerDay));


    Sprite vacc_sprite;
    vacc_sprite.setTexture(texture3);
    vacc_sprite.setScale(Vector2f(0.05, 0.05));

    //g³ówna pêtla symulacji
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //system("cls");
        if (frames == framerate) {
            system("cls");
            populationMove();
            board.printBoard();
        }

        ////DRUK GUI////

        //GLOWNA PLANSZA
        window.clear();
        window.draw(rect);
        for (int i = 0; i < healthyPopulationCount; i++) {
            healthyPopulation[i].moveSprite(framerate);
            window.draw(healthyPopulation[i].sprite);
        }
        for (int i = 0; i < sickPopulationCount; i++) {
            if (!sickPopulation[i].onQuarantine){
                sickPopulation[i].moveSprite(framerate);
                window.draw(sickPopulation[i].sprite);
            }
        }

        //LICZNIKI
        window.draw(header1);
        sick_counter.setString("Licznik chorej populacji: " + to_string(sickPopulationCount));
        window.draw(sick_counter);
        healthy_counter.setString("Licznik zdrowej populacji: " + to_string(healthyPopulationCount));
        window.draw(healthy_counter);
        quarantine_counter.setString("Licznik populacji na kwarantannie: " + to_string(quarantinePopulationCount));
        window.draw(quarantine_counter);
        death_counter.setString("Ilosc smierci: " + to_string(deathCount));
        window.draw(death_counter);

        //DANE CHOROBY
        window.draw(header2);
        window.draw(data1);
        window.draw(data2);

        //PLANSZA KWARANTANNY
        quarantine_rect.setSize(Vector2f(50 * quarantineBoard.width, 50));
        window.draw(quarantine_rect);
        for (int i = 0; i < quarantineBoard.board.size(); i++) {
            for (int j = 0; j < quarantineBoard.board[i].size(); j++) {
                quarantine_person.setPosition(Vector2f(100+j*50, 150 + (board.height+i)*50));
                window.draw(quarantine_person);
            }
        }

        //PROGRES SZCZEPIONKI
        window.draw(header3);
        if (vaccine.createPossibility) {
            if (!vaccine.created) {
                window.draw(data4);
                window.draw(data5);
                for (int i = 0; i < (days / 10) + 1;i++) {
                    if (i == (days / 10)) {
                        for (int j = 0; j < (days % 10); j++) {
                            vacc_sprite.setPosition(Vector2f(140 + board.width * 50 + 50 * j, 100 + (12 + i) * 50));
                            window.draw(vacc_sprite);
                        }
                    }
                    else {
                        for (int j = 0; j < 10; j++) {
                            vacc_sprite.setPosition(Vector2f(140 + board.width * 50 + 50 * j, 100 + (12 + i) * 50));
                            window.draw(vacc_sprite);
                        }

                    }
                }
            }
            else {
                window.draw(data3);
            }
        }

        window.display();


        /////////////////////////
        if (frames == framerate) {
            Vector2f cords;
            for (int i = 0; i < healthyPopulationCount; i++) {
                cords = healthyPopulation[i].sprite.getPosition();
            }
            for (int i = 0; i < sickPopulationCount; i++) {
                cords = sickPopulation[i].sprite.getPosition();
            }
            kill();
            recover();
            infect();
            if (vaccine.createPossibility) {
                if (!vaccine.created) {
                    vaccine.increaseVaccineDaysCount();
                }
                else {
                    cout << "Vaccine was created!" << endl;
                    vaccinate();
                    expirePopulationVaccine();
                }
            }
            moveToQuarantine();
            moveToBoard();
            quarantineBoard.printBoard(quarantinePopulationCount);
            frames = 0;
            if (checkEndingConditions()) {
                cout << "Osiagnieto warunki koncowe!" << endl;
                system("pause");
                break;
            }
            cout << "Days: " << days << " " << 10 * vaccine.createDifficulty << " " << (days / (10 * vaccine.createDifficulty)) + 1 << endl;
            days++;
        }
        frames++;
    }
}

