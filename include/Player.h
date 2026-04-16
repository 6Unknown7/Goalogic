#pragma once

#include <string>   // Библиотека (Работа с текстом)
#include <iostream> // Библиотека (Ввод/вывод)

using namespace std;

// Класс (Игрок)
class Player {
protected:
    string name, position;
    int shooting, passing, dribbling, defending, physics, stamina;
    bool isInjured;

    int validateStat(int value); // Валидация (Статистика)

public:
    // Конструктор (Игрок)
    Player(string n, string pos, int shot, int pass, int drib, int def, int phys, int stam = 100);
    virtual ~Player() = default;

    virtual int getOVR(); // Метод (Общий рейтинг "OVR")

    // Геттеры (Характеристики)
    string getName();
    string getPosition();
    int getShooting();
    int getPassing();
    int getDribbling();
    int getDefending();
    int getPhysics();
    int getStamina();
    bool getIsInjured();

    void setStamina(int value); // Валидация (Стамина)
    void setInjured(bool status); // Метод (Травма)
    string getColoredStamina(); // Метод (Цветная стамина)
    virtual void printStats(); // Метод (Карточка игрока)
};

// Класс (Вратарь)
class Goalkeeper : public Player {
private:
    int reflexes;
    int jumping;

public:
    // Конструктор (Вратарь)
    Goalkeeper(string n, string pos, int shot, int pass, int drib, int def, int phys, int refl, int jump, int stam = 100);
    
    int getOVR() override; // Метод (Общий рейтинг вратаря "OVR)
    
    // Геттеры (Рефлексы и прыжки)
    int getReflexes(); 
    int getJumping();

    void printStats() override; // Метод (Вывод статистик)
};