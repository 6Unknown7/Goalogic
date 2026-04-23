#include <iostream>   // Библиотека (Ввод/вывод)
#include <clocale>    // Библиотека (Русский язык)
#include <conio.h>    // Библиотека (Консоль)
#include <windows.h>  // Библиотека (Ввод/вывод)
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

    // Кодировка (Русский язык)
    setlocale(LC_ALL, "Russian"); 
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Team myTeam("FC GoaLogic"); // Создаем команду
    myTeam.loadPlayersFromFile("data/players.txt");

    Team opponent("AFC Goalogic"); // Создаем команду соперника
    opponent.addPlayer(new Player(PlayerStatus::Starter, "M. Salah", PlayerPosition::FWD, 84, 76, 87, 43, 87, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Starter, "H. Kane", PlayerPosition::FWD, 91, 79, 84, 32, 90, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Starter, "L. Martinez", PlayerPosition::FWD, 90, 76, 87, 35, 87, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Starter, "Pedri", PlayerPosition::MID, 82, 82, 77, 56, 69, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Starter, "C. Palmer", PlayerPosition::MID, 83, 88, 84, 50, 82, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Starter, "D. Olmo", PlayerPosition::MID, 74, 83, 73, 69, 80, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Starter, "T. Hernandez", PlayerPosition::DEF, 72, 85, 68, 77, 84, 100, 100));;
    opponent.addPlayer(new Player(PlayerStatus::Starter, "W. Saliba", PlayerPosition::DEF, 68, 84, 29, 95, 92, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Starter, "D. Huijsen", PlayerPosition::DEF, 63, 81, 37, 89, 79, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Starter, "J. Frimpong", PlayerPosition::DEF, 69, 80, 64, 83, 74, 100, 100));
    opponent.addPlayer(new Goalkeeper(PlayerStatus::Starter, "E. Martinez", PlayerPosition::GK, 23, 71, 22, 40, 77, 83, 82, 100, 100));
    opponent.addPlayer(new Goalkeeper(PlayerStatus::Substitute, "J. Garcia", PlayerPosition::GK, 31, 78, 25, 51, 82, 85, 88, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Substitute, "A. Serloth", PlayerPosition::FWD, 79, 74, 72, 34, 84, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Substitute, "F. Torres", PlayerPosition::FWD, 73, 69, 70, 29, 76, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Substitute, "L. Goretzka", PlayerPosition::MID, 75, 87, 68, 76, 82, 100, 100));
    opponent.addPlayer(new Player(PlayerStatus::Substitute, "C. Romero", PlayerPosition::DEF, 53, 76, 54, 81, 77, 100, 100));

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
            loadingEffect("Подготовка поля");
            Match currentMatch(&myTeam, &opponent);
            currentMatch.startQuickMatch();

            for (auto p : myTeam.roster) p->resetAfterMatch(); 
            for (auto p : opponent.roster) p->resetAfterMatch();
        }

        else if (choice == 2) {
            loadingEffect("Формирование турнирной сетки");
            cout << "\nДанный режим на этапе разработки...\n";
            pause();
        }

        else if (choice == 3) {
            cout << "\nСостав вашей команды:\n";
            myTeam.printTeam();
            cout << "\nСостав команды соперника:\n";
            opponent.printTeam();
            cout << "\nНажмите любую клавишу, чтобы вернуться в меню...\n";
            pause();
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
            << " Имя игрока,позиция,удар,пасс,дриблинг,защита,физика,мораль,стамина(необязательно),рефлексы,прыжки";
            pause();
        }

        else {
            cout << "\n[Ошибка!] Мяч вне поля! Выбери значения из меню.\n";
        }
    }

    return 0;
}