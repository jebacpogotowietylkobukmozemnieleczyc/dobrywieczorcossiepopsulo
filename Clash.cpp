#include "Clash.h"

Clash::Clash(const std::shared_ptr<User> &user1, const std::shared_ptr<User> &user2) :
        turnCount(0),
        hp1(user1->getHp()),
        hp2(user2->getHp()),
        mp1(user1->getMp()),
        mp2(user2->getMp()) {
    users.at(0) = user1;
    users.at(1) = user2;
    turn.fill(false);
}

void Clash::IncreaseTurn() {
    ++turnCount;
    turn.fill(false);
}

void Clash::ActiveTurn(const std::shared_ptr<User> &user) {
    if (users[0] == user)turn[0] = true;
    else if (users[1] == user)turn[1] = true;
    if (turn[0] && turn[1])IncreaseTurn();
}

std::string Clash::LoadData() {
    return "dc:" + std::to_string(hp1) + ":" + std::to_string(hp2) + ":" + std::to_string(mp1) + ":" +
           std::to_string(mp2) + ":" + users.at(0)->getName() + ":" + users.at(1)->getName() + ":;";
}

bool Clash::CheckTurn(const std::shared_ptr<User> &user) {
    if (user == users[0]) {
        return turn[1];
    }
    else if (user == users[1]) {
        return turn[0];
    }
    return false;
}

void Clash::Attack(const std::shared_ptr<User> &user, int newHp) {
    if (users[0] == user) {
        if (turn[0])
            return;
        hp2 = newHp;
        turn[0] = true;
    }
    else if (users[1] == user) {
        if (turn[1])
            return;
        hp1 = newHp;
        turn[1] = true;
    }
    if (turn[0] && turn[1])IncreaseTurn();
}

void Clash::SetMp(const std::shared_ptr<User> &user, int newMp) {
    if (users[0] == user) {
        mp1 = newMp;
    }
    else if (users[1] == user) {
        mp2 = newMp;
    }
}

bool Clash::CheckUser(const std::shared_ptr<User> &user) const {
    return user == users[0] || user == users[1];
}

bool Clash::CheckUsers(const std::shared_ptr<User> &user, const std::shared_ptr<User> &user2) const {
    return user == users[0] && user2 == users[1];
}

bool Clash::CheckRound(int round) {
    return turnCount > round;
}
