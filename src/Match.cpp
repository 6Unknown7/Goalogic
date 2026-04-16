#include <iostream>  // Библиотека (Ввод/вывод)
#include <ctime>     // Библиотека (Генератор)
#include <conio.h>   // Библиотека (Консоль)
#include <windows.h> // Библиотека (Функция Sleep)
#include "Match.h"
#include "Colors.h"

using namespace std;

// Функция (Загрузка)
void loadingEffect() {
    cout << "\nПодготовка поля";
    for (int i = 0; i < 3; i++) {
        Sleep(500);
        cout << ".";
    }
    cout << "\n";
}

// Функция (Пауза)
void pause() {
    cout << "\n ";
    _getch();
}

Match::Match(Team* h, Team* a) {
    homeTeam = h;
    awayTeam = a;
    srand(time(0));
}

// Функция (Только полевой игрок)
Player& Match::getRandomOutfieldPlayer(Team* team) {
    vector<Player*> outfield;
    for (auto p : team->roster) {
        if (p->getPosition() != "GK" && !p->getIsInjured()) outfield.push_back(p);
    }
    if (outfield.empty()) return *(team->roster[0]);
    return *outfield[rand() % outfield.size()];
}

// Функция (Рассчет успеха)
bool Match::calculateSuccess(Player& p, int homeStat, int oppStat) {
    double fatigueMultiplier = p.getStamina() / 100.0;
    int effectiveStat = homeStat * (fatigueMultiplier + fatigueMultiplier / 2);
    int total = effectiveStat + oppStat;
    if (total <= 0) return false;

    return (rand() % 100) < ((effectiveStat * 100) / total);
}

// Функция (Определение вратаря)
Player* Match::getGoalkeeper(Team* team) {
    for (Player* p : team->roster) {
        if (p->getPosition() == "GK") return p;
    }
    return nullptr;
}

// Функция (Безопасный ввод)
int Match::getSafeAction() {
    int action;

    while (!(cin >> action) || (action != 1 && action != 2)) {
        cout << "\n[Ошибка] Выберите 1 или 2: ";
        cin.clear();

        while (cin.get() != '\n');
    }
    return action;
}

// Функция (Генератор травм)
void Match::handleInjury(Player& p) {
    // Список вариантов травм
    vector<string> injuryTypes = {
        "растяжение икроножной мышцы",
        "вывих голеностопа",
        "перелом левой лодыжки",
        "разрыв задней поверхности бедра",
        "сотрясение мозга",
        "разрыв передней крестообразной связки",
        "разрыв задней крестообразной связки",
        "перелом ключицы",
        "разрыв мениска",
        "перелом большого пальца правой ноги"
    };

    // Пометка игрока
    p.setInjured(true);
    p.setStamina(0);

    string injury = injuryTypes[rand() % injuryTypes.size()];
    cout << "\n" << RED << BOLD << "\n[ТРАВМА!] " << RESET << p.getName() << " получил травму ( " << BOLD << injury << RESET << " ) и не может продолжать матч!" << endl;
}

// Функция (Травма)
void Match::handleStaminaAndInjury(Player& p, int drop) {
    if (p.getIsInjured()) return;

    p.setStamina(p.getStamina() - drop);

    int chance = 0;

    if (p.getStamina() <= 20) chance = 10;
    else if (p.getStamina() <= 15) chance = 15;
    else if (p.getStamina() <= 10) chance = 30;
    else if (p.getStamina() <= 5) chance = 50;
    else if (p.getStamina() == 0) chance = 90;
    else chance = 5;

    int physModifier = (50 - p.getPhysics()) / 3;

    chance += physModifier;

    if (chance < 0) chance = 0;

    if (chance > 0 && (rand() % 100) < chance) {
        handleInjury(p);
    }

    return;
}

// Функция (Контратака)
void Match::triggerCounterAttack() {

    Player& homePlayer = getRandomOutfieldPlayer(homeTeam);
    Player& oppPlayer = getRandomOutfieldPlayer(awayTeam);

    Player* hGK = getGoalkeeper(homeTeam);
    int gkSaveStat = (hGK != nullptr) ? hGK->getOVR() : 50;

    cout << "\n[!!!] Соперник перехватил мяч и летит в контратаку!" << endl;

    pause();

    cout << "" << oppPlayer.getName() << " приближается к воротам с мячом!" << endl;

    pause();

    cout << "" << homePlayer.getName() << " пытается прервать атаку..." << endl;
    cout << "Что делать? 1. Защищаться | 2. Ждать удара" << endl;
    cout << "Ваш выбор: ";

    int action;
    cin >> action;

    if (action == 1) {

        if (calculateSuccess(homePlayer, homePlayer.getDefending(), oppPlayer.getDribbling())) {
            cout << "\n[УСПЕХ!] " << homePlayer.getName() << " отобрал мяч, владение восстановлено!" << endl;
            handleStaminaAndInjury(homePlayer, 10);
            handleStaminaAndInjury(oppPlayer, 10);
        }

        else {
            cout << "\n[ОПАСНО!] " << oppPlayer.getName() << " филигранно обыграл и бьет по воротам..." << endl;
            handleStaminaAndInjury(homePlayer, 10);
            handleStaminaAndInjury(oppPlayer, 15);

            if (calculateSuccess(oppPlayer, oppPlayer.getShooting(), gkSaveStat)) {
                cout << "\n[ГОЛ!] " << oppPlayer.getName() << " мощно пробил и не оставил шансов вратарю!" << endl;
                scoreAway++;
                handleStaminaAndInjury(oppPlayer, 10);
            }

            else {
                cout << "\n[ФУХХХХ!] Вратарь спасает команду!" << endl;
                handleStaminaAndInjury(oppPlayer, 10);
            }

            if (hGK) {
                handleStaminaAndInjury(*hGK, 10);
                cout << "\nОстаток сил вратаря: " << hGK->getColoredStamina() << "%" << endl;
            }

            pause();
        }
    }

    else if (action == 2) {

        if (calculateSuccess(oppPlayer, oppPlayer.getShooting(), gkSaveStat)) {
            cout << "\n[ГОЛ!] " << oppPlayer.getName() << " мощно пробил и не оставил шансов вратарю!" << endl;
            scoreAway++;
            handleStaminaAndInjury(oppPlayer, 10);
        }

        else if (int(rand() % 100) > 80) {
            cout << "\n[УСПЕХ!] Повезло, мяч попал прямо в защитника!" << endl;
            handleStaminaAndInjury(oppPlayer, 10);
        }

        if (hGK) {
            handleStaminaAndInjury(*hGK, 10);
            cout << "\nОстаток сил вратаря: " << hGK->getColoredStamina() << "%" << endl;
        }
    }
}


// Функция (Быстрый матч)
void Match::startQuickMatch() {
    cout << "\n====================================" << endl;
    cout << "   МАТЧ НАЧИНАЕТСЯ: " << homeTeam->teamName << " vs " << awayTeam->teamName << endl;
    cout << "====================================\n" << endl;

    for (int i = 1; i <= 5; i++) {

        Player& hPlayer = getRandomOutfieldPlayer(homeTeam);
        Player& oPlayer = getRandomOutfieldPlayer(awayTeam);

        Player* oppGK = getGoalkeeper(awayTeam);
        int gkSaveStats = (oppGK != nullptr) ? oppGK->getOVR() : 50;

        cout << "--- ЭПИЗОД №" << i << " ---" << endl;
        cout << "Мяч у игрока: " << hPlayer.getName() << " (" << hPlayer.getPosition() << ")" << endl;
        cout << "Против него защищается:  " << oPlayer.getName() << " (Защита: " << oPlayer.getDefending() << ")" << endl;
        cout << "Что делаем? 1. Дриблинг | 2. Пас" << endl;
        cout << "Ваш выбор: ";

        int action;
        cin >> action;

        if (action == 1) {

            if (calculateSuccess(hPlayer, hPlayer.getDribbling(), oPlayer.getDefending())) {
                cout << "\n[!] " << hPlayer.getName() << " обыграл защитника!" << endl;
                cout << "Бьем по воротам? 1. Да | 2. Нет, пас назад" << endl;
                cout << "Ваш выбор: ";
                handleStaminaAndInjury(hPlayer, 15);
                handleStaminaAndInjury(oPlayer, 10);

                cin >> action;

                if (action == 1) {

                    if (calculateSuccess(hPlayer, hPlayer.getShooting(), gkSaveStats)) {
                        cout << "\n[ГООООЛ!] Счет становится солиднее!" << endl;
                        scoreHome++;
                        hPlayer.setStamina(hPlayer.getStamina() - 10);

                    }

                    else {
                        cout << "\n[СЕЙВ!] Вратарь на месте." << endl;
                        hPlayer.setStamina(hPlayer.getStamina() - 10);
                    }

                    if (oppGK) {
                        handleStaminaAndInjury(*oppGK, 10);
                        cout << "\nОстаток сил вратаря: " << oppGK->getColoredStamina() << "%" << endl;
                    }
                }

                else {
                    cout << "\nРешили не рисковать, атака продолжается позиционно." << endl;
                    handleStaminaAndInjury(hPlayer, 5);
                }
            }

            else {
                cout << "\n[ПОТЕРЯ!] Защитник отобрал мяч." << endl;
                handleStaminaAndInjury(hPlayer, 15);
                handleStaminaAndInjury(oPlayer, 10);
                triggerCounterAttack();
            }
        }

        else {
            if (calculateSuccess(hPlayer, hPlayer.getPassing(), 50)) {
                cout << "\n[ОК] Точный пас, владение сохранено." << endl;
                handleStaminaAndInjury(hPlayer, 5);
            }

            else {
                cout << "\n[!] Перехват! Соперник контратакует." << endl;
                handleStaminaAndInjury(hPlayer, 5);
                handleStaminaAndInjury(oPlayer, 5);
                triggerCounterAttack();
            }
        }

        cout << "\nОстаток сил " << hPlayer.getName() << ": " << hPlayer.getColoredStamina() << "%" << endl;
        cout << "\nОстаток сил " << oPlayer.getName() << ": " << oPlayer.getColoredStamina() << "%" << endl;
        cout << "\nТекущий счет: " << scoreHome << ":" << scoreAway << endl;
        cout << "\nНажмите любую клавишу для следующего хода...";

        pause();
    }

    cout << "====================================" << endl;
    cout << "ФИНАЛЬНЫЙ СВИСТОК!" << endl;

    if (scoreHome > scoreAway) cout << "ПОБЕДА! " << homeTeam->teamName << " выиграли матч!" << endl;

    else if (scoreHome < scoreAway) cout << "ПОРАЖЕНИЕ! " << awayTeam->teamName << " выиграли матч!" << endl;

    else cout << "НИЧЬЯ! 90 минут не смогли выявить победителя!" << endl;
    cout << "ИТОГОВЫЙ СЧЕТ: " << scoreHome << ":" << scoreAway << endl;
    cout << "====================================\n" << endl;
}