#include "Player.h"
#include "Colors.h"

using namespace std;

int Player::validateStat(int value) {
    if (value > 99) return 99;
    if (value < 1) return 1;
    return value;
}

Player::Player(string n, string pos, int shot, int pass, int drib, int def, int phys, int stam) {
    name = n;
    position = pos;
    shooting = validateStat(shot);
    passing = validateStat(pass);
    dribbling = validateStat(drib);
    defending = validateStat(def);
    physics = validateStat(phys);
    stamina = stam;
    isInjured = false;
}

int Player::getOVR() {
    if (position == "FWD") return (shooting * 0.7) + (dribbling * 0.3);
    else if (position == "DEF") return (defending * 0.8) + (passing * 0.2);
    else if (position == "MID") return (passing * 0.5) + (shooting * 0.2) + (dribbling * 0.3);
    return (shooting + passing + dribbling + defending) / 4;
}

string Player::getName() { return name; }
string Player::getPosition() { return position; }
int Player::getShooting() { return shooting; }
int Player::getPassing() { return passing; }
int Player::getDribbling() { return dribbling; }
int Player::getDefending() { return defending; }
int Player::getPhysics() { return physics; }
int Player::getStamina() { return stamina; }
bool Player::getIsInjured() { return isInjured; }

void Player::setStamina(int value) {
    if (value > 100) stamina = 100;
    else if (value < 0) stamina = 0;
    else stamina = value;
}

void Player::setInjured(bool status) { isInjured = status; }

string Player::getColoredStamina() {
    int s = getStamina();
    string sColor = RESET;
    if (stamina >= 70) sColor = GREEN;
    else if (stamina >= 40) sColor = YELLOW;
    else if (stamina >= 20) sColor = ORANGE;
    else sColor = RED;
    return sColor + to_string(s) + "%" + RESET;
}

void Player::printStats() {
    cout << "[" << position << "] " << name << " [OVR: " << getOVR() << "] "
        << " | Удар: " << shooting << " | Пас: " << passing
        << " | Дриблинг: " << dribbling << " | Защита: " << defending
        << " | Физика: " << physics << " | Выносливость: " << getColoredStamina() << "\n";
}

Goalkeeper::Goalkeeper(string n, string pos, int shot, int pass, int drib, int def, int phys, int refl, int jump, int stam)
    : Player(n, "GK", shot, pass, drib, def, phys, stam) {
    if (refl > 99) reflexes = 99; else if (refl < 1) reflexes = 1; else reflexes = refl;
    if (jump > 99) jumping = 99; else if (jump < 1) jumping = 1; else jumping = jump;
}

int Goalkeeper::getOVR() { return (reflexes * 0.4) + (jumping * 0.5) + (getPassing() * 0.1); }
int Goalkeeper::getReflexes() { return reflexes; }
int Goalkeeper::getJumping() { return jumping; }

void Goalkeeper::printStats() {
    cout << "[GK] " << getName() << " [OVR: " << getOVR() << "] "
        << " | Рефлексы: " << reflexes << " | Пас: " << passing
        << " | Прыжки: " << jumping << " | Физика: " << physics
        << " | Выносливость: " << getColoredStamina() << "\n";
}