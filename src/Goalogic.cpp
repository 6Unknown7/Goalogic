#include <iostream>   // Библиотека (Ввод/вывод)
#include <clocale>    // Библиотека (Русский язык)
#include <conio.h>    // Библиотека (Консоль)
#include "Colors.h"
#include "Player.h"
#include "Team.h"
#include "Match.h"

using namespace std;

// Функция (Главное меню) 
void showMenu() {
    system("cls");
    cout << "====================================\n";
    cout << "             GOALOGIC               \n";
    cout << "====================================\n";
    cout << "1. Быстрый матч\n";
    cout << "2. Режим Турнира\n";
    cout << "3. Команды\n";
    cout << "4. Создать игрока\n";
    cout << "5. Выход\n";
    cout << "9. Справка\n";
    cout << "====================================\n";
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    Team myTeam("FC GoaLogic"); // Создаем твою команду
    myTeam.loadPlayersFromFile("data/players.txt");

    Team opponent("AFC Goalogic"); // Создаем команду соперника
    opponent.addPlayer(new Player("M. Salah", "FWD", 84, 76, 87, 43, 87, 100));
    opponent.addPlayer(new Player("H. Kane", "FWD", 91, 79, 84, 32, 90, 100));
    opponent.addPlayer(new Player("L. Martinez", "FWD", 90, 76, 87, 35, 87, 100));
    opponent.addPlayer(new Player("Pedri", "MID", 82, 82, 77, 56, 69, 100));
    opponent.addPlayer(new Player("C. Palmer", "MID", 83, 88, 84, 50, 82, 100));
    opponent.addPlayer(new Player("D. Olmo", "MID", 74, 83, 73, 69, 80, 100));
    opponent.addPlayer(new Player("T. Hernandez", "DEF", 72, 85, 68, 77, 84, 100));;
    opponent.addPlayer(new Player("W. Saliba", "DEF", 68, 84, 29, 95, 92, 100));
    opponent.addPlayer(new Player("D. Huijsen", "DEF", 63, 81, 37, 89, 79, 100));
    opponent.addPlayer(new Player("J. Frimpong", "DEF", 69, 80, 64, 83, 74, 100));
    opponent.addPlayer(new Goalkeeper("E. Martinez", "GK", 23, 71, 22, 40, 77, 83, 82, 100));
    opponent.addPlayer(new Goalkeeper("J. Garcia", "GK", 31, 78, 25, 51, 82, 85, 88, 100));
    opponent.addPlayer(new Player("A. Serloth", "FWD", 79, 74, 72, 34, 84, 100));
    opponent.addPlayer(new Player("F. Torres", "FWD", 73, 69, 70, 29, 76, 100));
    opponent.addPlayer(new Player("L. Goretzka", "MID", 75, 87, 68, 76, 82, 100));
    opponent.addPlayer(new Player("C. Romero", "DEF", 53, 76, 54, 81, 77, 100));

    int choice;

    while (true) {
        showMenu();
        // Проверка на корректность ввода числа
        if (!(cin >> choice)) {
            cout << "\n[Ошибка] Вводи только цифры!\n";
            cin.clear(); // Сбрасываем ошибку
            while (cin.get() != '\n'); // Очищаем буфер ввода
            continue;
        }

        if (choice == 1) {
            loadingEffect();
            Match currentMatch(&myTeam, &opponent);
            currentMatch.startQuickMatch();

            for (auto p : myTeam.roster) p->setStamina(100), p->setInjured(false); // Восстанавливаем выносливость и травмы после матча
        }

        else if (choice == 2) {
            cout << "\n[!] Формирование турнирной сетки...\n\n";
            cout << "\nДанный режим на этапе разработки...\n\n";
        }

        else if (choice == 3) {
            cout << "\nСостав вашей команды:\n";
            myTeam.printTeam();
            cout << "\nСостав команды соперника:\n";
            opponent.printTeam();
            cout << "\nНажмите любую клавишу, чтобы вернуться в меню...\n\n";
            _getch();
        }

        else if (choice == 4) {
            myTeam.createManualPlayer();
        }

        else if (choice == 5) {
            cout << "\nФинальный свисток! До встречи в Goalogic.\n";
            return 0;
        }

        else if (choice == 9) {
            cout << "\nПример создания .txt файла с игроком/ами:"
            << " Имя игрока,позиция,удар,пасс,дриблинг,защита,физика,стамина(необязательно),рефлексы,прыжки\n\n";
        }

        else {
            cout << "\n[Ошибка] Мяч вне поля! Выбери 1, 2 или 3.\n\n";
        }
    }

    return 0;
}