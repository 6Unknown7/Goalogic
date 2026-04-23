#include <iostream>
#include <fstream>
#include <sstream>
#include "Team.h"
#include "Colors.h"

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

Player* Team::findStarterByPosition(PlayerPosition pos) {
    for (auto p : roster) {
        // Ищем того, кто: 1. В старте, 2. На нужной позиции
        if (p->getStatus() == PlayerStatus::Starter && p->getPosition() == pos) {
            return p;
        }
    }
    return nullptr; // Если вдруг не нашли
}

void Team::printTeam() {
    cout << "=== Состав команды " << teamName << ":" << "=== \n";
    int teamTotalOVR = 0;

    if (roster.empty()) {
        cout << "В команде нет игроков.\n";
        return;
    }

    for (int i = 0; i < roster.size(); i++) {
        roster[i]->printStats(i + 1);
        teamTotalOVR += roster[i]->getOVR();
    }

    if (roster.size() > 0) {
        int avgOVR = teamTotalOVR / roster.size();
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

        auto get = [&](int idx) { return stoi(data[idx]); };
		PlayerStatus s = static_cast<PlayerStatus>(stoi(data[0]));
        PlayerPosition pos = static_cast<PlayerPosition>(stoi(data[2]));

        if (data.size() == 9) {
            addPlayer(new Player(s, data[1], pos, get(3), get(4), get(5), get(6), get(7), get(8)));
        }
        else if (data.size() == 10) {
            addPlayer(new Player(s, data[1], pos, get(3), get(4), get(5), get(6), get(7), get(8), get(9)));
        }
        else if (data.size() == 11) {
            addPlayer(new Goalkeeper(s, data[1], pos, get(3), get(4), get(5), get(6), get(7), get(8), get(9), get(10)));
        }
        else if (data.size() == 12) {
            addPlayer(new Goalkeeper(s, data[1], pos, get(3), get(4), get(5), get(6), get(7), get(8), get(9), get(10), get(11)));
        }
    }
    file.close();
    cout << GREEN << "[Успех] Загружено игроков из файла: " << roster.size() << RESET << endl;
}

void Team::createManualPlayer() {
    string n;
    int sIdx, posIdx, shot, pass, drib, def, phys, stam;

    cout << "\n--- СОЗДАНИЕ НОВОГО ИГРОКА ---" << endl;
    cout << "Введите имя: ";
    cin.ignore();
    getline(cin, n);

    cout << "Выберите позицию (1-НАП, 2-ПЗЩ, 3-ЗАЩ): "; cin >> posIdx;
    cout << "Удар (1-99): "; cin >> shot;
    cout << "Пас (1-99): "; cin >> pass;
    cout << "Дриблинг (1-99): "; cin >> drib;
    cout << "Защита (1-99): "; cin >> def;
    cout << "Физика (1-99): "; cin >> phys;
    cout << "Выберите роль в команде (0 - Основной, 1 - Запасной, 2 - Резервный): "; cin >> sIdx;
    stam = 100;

    PlayerStatus s = static_cast<PlayerStatus>(sIdx);
    PlayerPosition pos = static_cast<PlayerPosition>(posIdx);
    addPlayer(new Player(s, n, pos, shot, pass, drib, def, phys, stam));
    cout << GREEN << "\n[Система] Игрок " << n << " успешно создан и зачислен в состав!" << RESET << endl;
}