#pragma once

#include "Team.h"

// Функция (Загрузка)
void loadingEffect();

// Функция (Пауза)
void pause();

// Класс (Матч)
class Match {
public:
    Team* homeTeam;
    Team* awayTeam;
    int scoreHome = 0;
    int scoreAway = 0;

    Match(Team* h, Team* a);

    Player& getRandomOutfieldPlayer(Team* team); // Функция (Только полевой игрок)
    bool calculateSuccess(Player& p, int homeStat, int oppStat); // Функция (Рассчет успеха)
    Player* getGoalkeeper(Team* team); // Функция (Определение вратаря)
    int getSafeAction(); // Функция (Безопасный ввод)
    void handleInjury(Player& p); // Функция (Генератор травм)
    void handleStaminaAndInjury(Player& p, int drop); // Функция (Травма)
    void triggerCounterAttack(); // Функция (Контратака)
    void startQuickMatch(); // Функция (Быстрый матч)
};