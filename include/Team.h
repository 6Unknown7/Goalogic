#pragma once

#include <string>   // Библиотека (Работа с текстом)
#include <vector>   // Библиотека (Векторы)
#include "Player.h" 

using namespace std;

// Класс (Команда)
class Team {
public:
    string teamName; // Название команды
    vector<Player*> roster; // Вектор (Состав)

    Team(string tName); // Конструктор
    ~Team(); // Деструктор
	Player* findStarterByPosition(PlayerPosition pos); // Метод (Найти стартового игрока по позиции)
    void addPlayer(Player* p); // Функция (Добавление игрока)
    void printTeam(); // Функция (Вывод команды)
    void loadPlayersFromFile(string filename); // Функция (Подгрузка игроков из внешнего файла)
    void createManualPlayer(); // Функция (Создать игрока через консоль)
};