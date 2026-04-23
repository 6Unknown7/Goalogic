#include <iostream>  // Библиотека (Ввод/вывод)
#include <ctime>     // Библиотека (Генератор)
#include <conio.h>   // Библиотека (Консоль)
#include <windows.h> // Библиотека (Функция Sleep)
#include "Match.h"
#include "Colors.h"

using namespace std;

// Функция (Загрузка)
void loadingEffect(string message) {
    cout << "\n" << message;
    for (int i = 0; i < 3; i++) {
        Sleep(500);
        cout << ".";
    }
    cout << "\n";
}

// Функция (Пауза)
void pause() {
    cout << "\n";
    _getch();
}

// Конструктор (Матч)
Match::Match(Team* h, Team* a) {
    homeTeam = h;
    awayTeam = a;
    srand(time(0));
}

// Метод (Только полевой игрок)
Player& Match::getRandomOutfieldPlayer(Team* team) {
    vector<Player*> outfield;
    for (auto p : team->roster) {
        if (p->getPlayerPosition() != "ВРТ" && p->getStatus() == PlayerStatus::Starter) outfield.push_back(p);
    }
    if (outfield.empty()) return *(team->roster[0]);
    return *outfield[rand() % outfield.size()];
}

// Функция (Меню замен)
void Match::showSubstitutionMenu(Team* team) {
    if (homeSubsLeft <= 0) {
        cout << RED << "\n[!] Лимит замен исчерпан!" << RESET << endl;
        return;
    }
    vector<Player*> starters;
    vector<Player*> subs;
    vector<Player*> reserves;
    vector<Player*> notInSquad;

    for (auto p : team->roster) {
        if (p->getStatus() == PlayerStatus::Starter || p->getStatus() == PlayerStatus::Injured)
            starters.push_back(p);
        if (p->getStatus() == PlayerStatus::Substitute || p->getStatus() == PlayerStatus::Reserve)
            subs.push_back(p);
        if (p->getStatus() == PlayerStatus::Suspended || p->getStatus() == PlayerStatus::Injured)
            notInSquad.push_back(p);
    }

    cout << "\n--- Меню замен: ---" << endl;

    cout << "Выберите кого заменить: \n" << endl;
    for (int i = 0; i < starters.size(); i++) {
		string health = (starters[i]->getStatus() == PlayerStatus::Injured) ? " [ТРАВМА]" : "";
        cout << i + 1 << ". " << starters[i]->getName() << " [" << starters[i]->getPlayerPosition() << "]" << " (" << starters[i]->getColoredStamina() << ")" << health << endl;
    }
	int offIdx; cin >> offIdx; offIdx--;

    cout << "\n--- Меню замен: ---" << endl;

    cout << "Выберите кого выпустить: \n" << endl;
    for (int i = 0; i < subs.size(); i++) {
        cout << i + 1 << ". " << subs[i]->getName() << " [" << subs[i]->getPlayerPosition() << "]" << " (" << subs[i]->getColoredStamina() << ")" << endl;
    }
    int onIdx; cin >> onIdx; onIdx--;

    if (offIdx >= 0 && offIdx < starters.size() && onIdx >= 0 && onIdx < subs.size()) {
        Player* playerOff = starters[offIdx];
        Player* playerOn = subs[onIdx];

        playerOff->setStatus(PlayerStatus::Substitute);
        playerOn->setStatus(PlayerStatus::Starter);

        homeSubsLeft--;
        cout << GREEN << "\n[ЗАМЕНА] " << playerOn->getName() << " выходит вместо " << playerOff->getName() << "!\n" << RESET << endl;
    }
}  

// Функция (Рассчет успеха)
bool Match::calculateSuccess(Player& p, int homeStat, int oppStat) {
    double fatigueMultiplier = p.getStamina() / 100.0;
    double moraleMultiplier = 0.9 + (p.getMorale() / 500.0);
    double effectiveStat = homeStat * fatigueMultiplier * moraleMultiplier;
    int total = effectiveStat + oppStat;
    if (total <= 0) return false;
	int chance = (effectiveStat * 100) / total;
    return (rand() % 100) < ((effectiveStat * 100) / total);
}

// Метод (Определение вратаря)
Player* Match::getGoalkeeper(Team* team) {
    for (Player* p : team->roster) {
        if (p->getPlayerPosition() == "GK" && p->getStatus() == PlayerStatus::Starter) return p;
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
        "перелом лодыжки",
        "разрыв задней поверхности бедра",
        "сотрясение мозга",
        "разрыв передней крестообразной связки",
        "разрыв задней крестообразной связки",
        "перелом ключицы",
        "разрыв мениска",
        "перелом большого пальца стопы",
        "рассечение брови",
        "перелом носовой перегородки",
        "растяжение малоберцовых сухожилий голеностопа",
        "разрыв ахилла",
        "ушиб голени"
    };

    // Пометка игрока
    p.setStamina(0);
	p.setStatus(PlayerStatus::Injured);

    string injury = injuryTypes[rand() % injuryTypes.size()];
    cout << RED << BOLD << "\n[ТРАВМА!] " << RESET << p.getName() << " получил травму (" << BOLD << RED << injury << RESET << ") и не может продолжать матч!" << endl;
}

// Функция (Травма)
void Match::handleStaminaAndInjury(Player& p, int drop) {

    p.setStamina(p.getStamina() - drop);

    if (p.getStatus() == PlayerStatus::Injured || p.getStatus() == PlayerStatus::Suspended) return;

    int chance = 0;
	int currentStamina = p.getStamina();

    if (currentStamina <= 20) chance = 10;
    else if (currentStamina <= 15) chance = 15;
    else if (currentStamina <= 10) chance = 30;
    else if (currentStamina <= 5) chance = 50;
    else if (currentStamina == 0) chance = 90;
    else chance = 5;

    int physModifier = (50 - p.getPhysics()) / 3;

    chance += physModifier;

    if (chance > 100) chance = 100;
    if (chance < 0) chance = 0;

    if (chance > 0 && (rand() % 100) < chance) {
        handleInjury(p);
    }

    return;
}

int Match::getMenuChoice() {
    int choice;
    while (true) {
        cout << "Нуждаетесь в замене? Нажмите 1 для начала момента или 0 для замены: ";
        if (!(cin >> choice)) {
            cin.clear();
            while (cin.get() != '\n');
            continue;
        }

        if (choice == 0) {
            showSubstitutionMenu(homeTeam); 
        }
        else {
            return choice;
        }
    }
}

// Функция (Контратака)
void Match::triggerCounterAttack() {

    Player* homePlayer = &getRandomOutfieldPlayer(homeTeam);
    Player* oppPlayer = &getRandomOutfieldPlayer(awayTeam);
    Player* hGK = getGoalkeeper(homeTeam);

    int gkSaveStat = (hGK != nullptr) ? hGK->getOVR() : 50;

    cout << "\n[ОПАСНО!] Соперник перехватил мяч и летит в контратаку!" << endl;

    pause();

    cout << "" << oppPlayer->getName() << " приближается к воротам с мячом!" << endl;

    pause();

    cout << "" << homePlayer->getName() << " пытается прервать атаку..." << endl;
    cout << "Выберите действие: 1. Попытаться отобрать | 2. Пропустить : ";

	int action;
    cin >> action;

    if (action == 1) {

        if (calculateSuccess(*homePlayer, homePlayer->getDefending(), oppPlayer->getDribbling())) {
            cout << "\n[УСПЕХ!] " << homePlayer->getName() << " отобрал мяч, владение восстановлено!\n" << endl;
            handleStaminaAndInjury(*homePlayer, 10);
            handleStaminaAndInjury(*oppPlayer, 10);
        }

        else {
            cout << "\n[ОПАСНО!] " << oppPlayer->getName() << " филигранно обыграл и бьет по воротам..." << endl;
            handleStaminaAndInjury(*homePlayer, 10);
            handleStaminaAndInjury(*oppPlayer, 15);

            if (calculateSuccess(*oppPlayer, oppPlayer->getShooting(), gkSaveStat)) {
                cout << "\n[ГОООООЛ!] " << oppPlayer->getName() << " мощно пробил и не оставил шансов вратарю!" << endl;
                scoreAway++;
                handleStaminaAndInjury(*oppPlayer, 10);
            }

            else {
                cout << "\n[СЕЙВ!] Вратарь спасает команду!" << endl;
                handleStaminaAndInjury(*oppPlayer, 10);
            }

            if (hGK) {
                handleStaminaAndInjury(*hGK, 10);
                cout << "\nОстаток сил вратаря: " << hGK->getColoredStamina() << endl;
            }

            pause();
        }
    }

    else if (action == 2) {

        if (calculateSuccess(*oppPlayer, oppPlayer->getShooting(), gkSaveStat)) {
            cout << "\n[ГОООООЛ!] " << oppPlayer->getName() << " мощно пробил и не оставил шансов вратарю!" << endl;
            scoreAway++;
            handleStaminaAndInjury(*oppPlayer, 10);
        }

        else if (int(rand() % 100) > 80) {
            cout << "\n[УСПЕХ!] Повезло, мяч попал прямо в защитника!" << endl;
            handleStaminaAndInjury(*oppPlayer, 10);
        }

        if (hGK) {
            handleStaminaAndInjury(*hGK, 10);
            cout << "\nОстаток сил вратаря: " << hGK->getColoredStamina() << endl;
        }
    }
}


// Функция (Быстрый матч)
void Match::startQuickMatch() {
    int totalEpisodes = (rand() % 8) + 3; // Количество эпизодов в матче
    cout << "\n====================================" << endl;
    cout << "МАТЧ НАЧИНАЕТСЯ: " << homeTeam->teamName << " vs " << awayTeam->teamName << endl;
    cout << "====================================\n" << endl;

    for (int i = 1; i <= totalEpisodes ; i++) {
            
        // Цикл (Перерыв)
        if (i == totalEpisodes / 2) {
            cout << "\n--- Перерыв: Команды уходят в подтрибунку ---";
            pause();

            loadingEffect("Тренер разбирает командную игру");

            for (Player* p : homeTeam->roster) {

                if (scoreHome > scoreAway) {
                    int talkEffect = (rand() % 11) + 5;
                    p->setMorale(p->getMorale() + talkEffect);
                }

                else if (scoreHome < scoreAway) {
                    int talkEffect = (rand() % 6) - 10;
                    p->setMorale(p->getMorale() + talkEffect);
                }

                else {
                    int talkEffect = (rand() % 6);
					p->setMorale(p->getMorale() + talkEffect);
                }
            }

            if (scoreHome > scoreAway) {
                cout << "\nТренер похвалил команду за хорошую игру." << endl << GREEN << "\nНастроение команды улучшилось!" << RESET << endl;
            }
            
            else if (scoreHome < scoreAway) {
                cout << "\nТренер напихал игрокам за плохую игру и ошибки." << endl << RED << "\nНастроение команды ухудшилось!" << RESET << endl;
            }
            
            else {
                cout << "\nТренер призвал команду собраться и показать характер во втором тайме." << endl << GREEN << "\nНастроение команды незначительно улучшилось!" << RESET << endl;
            }
            pause();


			cout << "--- Второй тайм начинается ---\n" << endl;

            pause();
        }

            // Цикл (Обязательная замена)
            for (Player* p : homeTeam->roster) {
                if (p->getStatus() == PlayerStatus::Injured) {
                    PlayerPosition injuredPos = p->getPosition();

                    cout << RED << "========================================" << RESET << endl;
                    cout << RED << "[!!!] ТРАВМА: " << p->getName() << " не может продолжать!" << RESET << endl;
                    cout << RED << "========================================\n" << RESET << endl;

                    while (p->getStatus() == PlayerStatus::Injured) {
                        if (homeSubsLeft <= 0) {
                            cout << RED << "Замен нет! Игрок покидает поле, играем в меньшинстве." << RESET << endl;
                            p->setStatus(PlayerStatus::Suspended);
                            break;
                        }
                        cout << YELLOW << "Вы обязаны заменить травмированного: " << p->getName() << RESET << endl;
                        showSubstitutionMenu(homeTeam);
                    }
                }
            }

        Player* hPlayer = &getRandomOutfieldPlayer(homeTeam);
        Player* oPlayer = &getRandomOutfieldPlayer(awayTeam);
        Player* oppGK = getGoalkeeper(awayTeam);
        int gkSaveStats = (oppGK != nullptr) ? oppGK->getOVR() : 50;

        cout << "--- ЭПИЗОД №" << i << " ---" << endl;
        int choice;
        choice = getMenuChoice();
       
        cout << "Мяч у игрока: " << hPlayer->getName() << endl;
        cout << "Против него защищается:  " << oPlayer->getName() << " (Защита: " << oPlayer->getDefending() << ")" << endl;
        cout << "Выберите действие: 1. Дриблинг | 2. Пас : ";

        int action;
		cin >> action;

        // Цикл (Матч)
        if (action == 1) {

            if (calculateSuccess(*hPlayer, hPlayer->getDribbling(), oPlayer->getDefending())) {
                cout << "\n[!] " << hPlayer->getName() << " обыграл защитника!" << endl;
                cout << "Выберите действие: 1. Удар | 2. Пас : ";

                handleStaminaAndInjury(*hPlayer, 15);
                handleStaminaAndInjury(*oPlayer, 10);

                int action;
                cin >> action;

                if (action == 1) {

                    if (calculateSuccess(*hPlayer, hPlayer->getShooting(), gkSaveStats)) {
                        cout << "\n[ГОООООЛ!] Счет становится солиднее!" << endl;
                        scoreHome++;
                        hPlayer->setStamina(hPlayer->getStamina() - 10);

                    }

                    else {
                        cout << "\n[СЕЙВ!] Вратарь на месте." << endl;
                        hPlayer->setStamina(hPlayer->getStamina() - 10);
                    }

                    if (oppGK) {
                        handleStaminaAndInjury(*oppGK, 10);
                        cout << "Остаток сил вратаря: " << oppGK->getColoredStamina() << endl;
                    }
                }

                else {
                    cout << "Решили не рисковать, атака продолжается позиционно." << endl;
                    handleStaminaAndInjury(*hPlayer, 5);
                }
            }

            else {
                cout << "\n[ПОТЕРЯ!] Защитник отобрал мяч." << endl;
                handleStaminaAndInjury(*hPlayer, 15);
                handleStaminaAndInjury(*oPlayer, 10);
                triggerCounterAttack();
            }
        }

        else {
            if (calculateSuccess(*hPlayer, hPlayer->getPassing(), 50)) {
                cout << "\n[ОК] Точный пас, владение сохранено." << endl;
                handleStaminaAndInjury(*hPlayer, 5);
            }

            else {
                cout << "\n[ОПАСНО!] Перехват! Соперник контратакует." << endl;
                handleStaminaAndInjury(*hPlayer, 5);
                handleStaminaAndInjury(*oPlayer, 5);
                triggerCounterAttack();
            }
        }

        cout << "Остаток сил " << hPlayer->getName() << ": " << hPlayer->getColoredStamina() << endl;
        cout << "Остаток сил " << oPlayer->getName() << ": " << oPlayer->getColoredStamina() << endl;
        cout << "\nТекущий счет: " << scoreHome << ":" << scoreAway << endl;
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