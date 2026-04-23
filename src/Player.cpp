#include "Player.h"
#include "Colors.h"

using namespace std;

int Player::validateStat(int value) {
    if (value > 99) return 99;
    if (value < 1) return 1;
    return value;
}

Player::Player(PlayerStatus s, string n, PlayerPosition pos, int shot, int pass, int drib, int def, int phys, int mor, int stam) {
    status = s;
    baseStatus = s;
    name = n;
    position = pos;
    shooting = validateStat(shot);
    passing = validateStat(pass);
    dribbling = validateStat(drib);
    defending = validateStat(def);
    physics = validateStat(phys);
    stamina = stam;
	baseStamina = stam;
    morale = mor;
}

string Player::getPlayerPosition() {
    switch (position) {
    case PlayerPosition::FWD: return "НАП";
    case PlayerPosition::MID: return "ПЗЩ";
    case PlayerPosition::DEF: return "ЗАЩ";
    case PlayerPosition::GK: return "ВРТ";
    default:                 return "---";
    }
}

int Player::getOVR() {
    if (position == PlayerPosition::FWD) return (shooting * 0.7) + (dribbling * 0.3);
    else if (position == PlayerPosition::MID) return (passing * 0.5) + (shooting * 0.2) + (dribbling * 0.3);
    else if (position == PlayerPosition::DEF) return (defending * 0.8) + (passing * 0.2);
    return (shooting + passing + dribbling + defending) / 4;
}


void Player::setStatus(PlayerStatus newStatus) {
    status = newStatus;
}

void Player::resetAfterMatch() {
    stamina = baseStamina;
    status = baseStatus; 
}

PlayerStatus Player::getStatus() { return status; }
string Player::getName() { return name; }
PlayerPosition Player::getPosition() { return position; }
int Player::getShooting() { return shooting; }
int Player::getPassing() { return passing; }
int Player::getDribbling() { return dribbling; }
int Player::getDefending() { return defending; }
int Player::getPhysics() { return physics; }
int Player::getStamina() { return stamina; }
int Player::getMorale() { return morale; }

void Player::setStamina(int value) {
    if (value > 100) stamina = 100;
    else if (value < 0) stamina = 0;
    else stamina = value;
}

void Player::setMorale(int value) {
    if (value > 100) morale = 100;
    else if (value < 0) morale = 0;
    else morale = value;
}

string Player::getColoredStamina() {
    int s = getStamina();
    string sColor = RESET;
    if (stamina >= 70) sColor = GREEN;
    else if (stamina >= 40) sColor = YELLOW;
    else if (stamina >= 20) sColor = ORANGE;
    else sColor = RED;
    return sColor + to_string(s) + "%" + RESET;
}

string Player::getColoredMorale() {
    int s = getMorale();
    string sColor = RESET;
    if (morale >= 70) sColor = GREEN;
    else if (morale >= 40) sColor = YELLOW;
    else if (morale >= 20) sColor = ORANGE;
    else sColor = RED;
    return sColor + to_string(s) + "%" + RESET;
}

string Player::getStatusString() {
    switch (status) {
        case PlayerStatus::Starter:    return "[ОСН]";
        case PlayerStatus::Substitute: return "[ЗАП]";
		case PlayerStatus::Reserve:    return "[РЕЗ]";
        case PlayerStatus::Injured:    return "[ТРАВМА]";
		case PlayerStatus::Suspended:  return "[ДИСКВАЛ]";
        default:                       return "[---]";
    }
}

void Player::printStats(int index) {
    cout << (index > 0 ? to_string(index) + "." : "") << "[" << getPlayerPosition() << "] " << name << " [OVR: " << getOVR() << "] "
        << " | Удар: " << shooting << " | Пас: " << passing
        << " | Дриблинг: " << dribbling << " | Защита: " << defending
        << " | Физика: " << physics << " | Мораль: " << getColoredMorale() << " | Выносливость: " << getColoredStamina() << " | Статус: " << getStatusString() << "\n";
}

Goalkeeper::Goalkeeper(PlayerStatus s, string n, PlayerPosition pos, int shot, int pass, int drib, int def, int phys, int refl, int jump, int mor, int stam)
    : Player(s, n, PlayerPosition::GK, shot, pass, drib, def, phys, mor, stam) {
    reflexes = validateStat(refl);
    jumping = validateStat(jump);
}

int Goalkeeper::getOVR() { return (reflexes * 0.4) + (jumping * 0.5) + (getPassing() * 0.1); }
int Goalkeeper::getReflexes() { return reflexes; }
int Goalkeeper::getJumping() { return jumping; }

void Goalkeeper::printStats(int index) {
    cout << (index > 0 ? to_string(index) + "." : "") << "." << "[ВРТ] " << getName() << " [OVR: " << getOVR() << "] "
        << " | Рефлексы: " << reflexes << " | Пас: " << passing
        << " | Прыжки: " << jumping << " | Физика: " << physics
        << " | Мораль: " << getColoredMorale() << " | Выносливость: " << getColoredStamina() << " | Статус: " << getStatusString() << "\n";
}