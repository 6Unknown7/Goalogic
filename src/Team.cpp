#include "Team.h"
#include "Colors.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Team::Team(string tName) {
    teamName = tName;
}

Team::~Team() {
    for (Player* p : roster) {
        delete p;
    }
    roster.clear();
}

void Team::addPlayer(Player* p) {
    roster.push_back(p);
}

void Team::printTeam() {
    cout << "=== Состав команды " << teamName << ":" << "=== \n";
    int TeamTotalOVR = 0;

    if (roster.empty()) {
        cout << "В команде нет игроков.\n";
        return;
    }

    for (Player* p : roster) {
        p->printStats();
        TeamTotalOVR += p->getOVR();
    }

    if (roster.size() > 0) {
        int avgOVR = TeamTotalOVR / roster.size();
        cout << "---------------------------" << endl;
        cout << "Средний рейтинг команды: [" << avgOVR << "]" << endl;
        cout << "-----------------------" << endl;
    }
    cout << "====================================\n";
}

void Team::loadPlayersFromFile(string filename) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << RED << BOLD << "[ОШИБКА] Не удалось открыть файл: " << filename << RESET << endl;
        return;
    }

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string part;
        vector<string> data;

        while (getline(ss, part, ',')) {
            part.erase(0, part.find_first_not_of(" \t\r\n"));
            part.erase(part.find_last_not_of(" \t\r\n") + 1);
            if (!part.empty()) {
                data.push_back(part);
            }
        }

        if (data.size() == 7) {
            addPlayer(new Player(data[0], data[1], stoi(data[2]), stoi(data[3]), stoi(data[4]), stoi(data[5]), stoi(data[6])));
        }
        else if (data.size() == 8) {
            addPlayer(new Player(data[0], data[1], stoi(data[2]), stoi(data[3]), stoi(data[4]), stoi(data[5]), stoi(data[6]), stoi(data[7])));
        }
        else if (data.size() == 9) {
            addPlayer(new Goalkeeper(data[0], "GK", stoi(data[2]), stoi(data[3]), stoi(data[4]), stoi(data[5]), stoi(data[6]), stoi(data[7]), stoi(data[8])));
        }
        else if (data.size() == 10) {
            addPlayer(new Goalkeeper(data[0], "GK", stoi(data[2]), stoi(data[3]), stoi(data[4]), stoi(data[5]), stoi(data[6]), stoi(data[7]), stoi(data[8]), stoi(data[9])));
        }
    }
    file.close();
    cout << GREEN << "[Успех] Загружено игроков из файла: " << roster.size() << RESET << endl;
}

void Team::createManualPlayer() {
    string n, pos;
    int shot, pass, drib, def, phys, stam;

    cout << "\n--- СОЗДАНИЕ НОВОГО ИГРОКА ---" << endl;
    cout << "Введите имя: ";
    cin.ignore();
    getline(cin, n);

    cout << "Введите позицию (FWD, MID, DEF): "; cin >> pos;
    cout << "Удар (1-99): "; cin >> shot;
    cout << "Пас (1-99): "; cin >> pass;
    cout << "Дриблинг (1-99): "; cin >> drib;
    cout << "Защита (1-99): "; cin >> def;
    cout << "Физика (1-99): "; cin >> phys;
    stam = 100;

    addPlayer(new Player(n, pos, shot, pass, drib, def, phys, stam));
    cout << GREEN << "\n[Система] Игрок " << n << " успешно создан и зачислен в состав!" << RESET << endl;
}