#pragma once

#include <string>   // Библиотека (Работа с текстом)
#include <iostream> // Библиотека (Ввод/вывод)

using namespace std;

// Функция (Статус игроков)
enum class PlayerStatus {
    Starter = 0,    // Основа
    Substitute = 1, // Запас
    Reserve = 2,    // Резерв
    Injured = 3,    // Травма
    Suspended = 4   // Дисквалификация
};

// Функция (Позиция игрока)
enum class PlayerPosition {
    FWD = 1, // Нападающий (НАП)
    MID = 2, // Полузащитник (ПЗЩ)
    DEF = 3, // Защитник (ЗАЩ)
    GK = 0   // Вратарь (ВРТ)
};

// Класс (Игрок)
class Player {
protected:
    PlayerStatus status;     // Статус
	PlayerStatus baseStatus; // Изначальный статус
    PlayerPosition position; // Позиция
    string name;             // Имя
    int shooting;            // Удар 
    int passing;             // Пасс
    int dribbling;           // Дриблинг
    int defending;           // Защита
    int physics;             // Физика
    int stamina;             // Выносливость
    int baseStamina;         // Изначальная выносливость
    int morale = 50;         // Мораль

    int validateStat(int value); // Валидация (Статистика)

public:
    // Конструктор (Игрок)
    Player(PlayerStatus s, string n, PlayerPosition pos, int shot, int pass, int drib, int def, int phys, int mor, int stam = 100);
    virtual ~Player() = default;

    virtual int getOVR(); // Метод (Общий рейтинг "OVR")

    // Геттеры
    PlayerStatus getStatus();     // Статус
    PlayerPosition getPosition(); // Позиция
    string getName();             // Имя
    int getShooting();            // Удар
    int getPassing();             // Пасс
    int getDribbling();           // Дриблинг
    int getDefending();           // Защита
    int getPhysics();             // Физика
    int getStamina();             // Стамина
    int getMorale();              // Мораль

    // Сеттеры
    void setStamina(int value); // Стамина
    void setMorale(int mor);    // Мораль

    // Функции 
    string getPlayerPosition();             // Поиск по позиции
    string getColoredStamina();             // Цветная стамина
    string getColoredMorale();              // Цветная мораль
	string getStatusString();               // Статус игрока
    virtual void printStats(int index);     // Карточка игрока
    void setStatus(PlayerStatus newStatus); // Статус игрока
	void resetAfterMatch();                 // Сброс после матча
};

// Класс (Вратарь)
class Goalkeeper : public Player {
private:
    int reflexes;
    int jumping;

public:
    // Конструктор (Вратарь)
    Goalkeeper(PlayerStatus s, string n, PlayerPosition pos, int shot, int pass, int drib, int def, int phys, int refl, int jump, int mor, int stam = 100);
    
    int getOVR() override; // Метод (Общий рейтинг вратаря "OVR)
    
    // Геттеры
    int getReflexes(); // Рефлексы
    int getJumping();  // Прыжки

    void printStats(int index) override; // Метод (Вывод статистик)
};