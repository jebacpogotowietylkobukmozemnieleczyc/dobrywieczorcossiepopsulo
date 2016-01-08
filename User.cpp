#include "User.h"

bool User::Login(std::string name, std::string password) const {
    return name == User::name && password == User::password && !User::logged;
}

bool User::CheckName(std::string name) const {
    return name == User::name;
}

void User::AddItem(int id) {
    have.push_back(id);
}

bool User::DeleteItem(int id) {
    auto it = std::find(have.begin(), have.end(), id);
    if (it != have.end()) {
        have.erase(it);
        return true;
    }
    return false;
}

bool User::SellItem(int id, int prize) {
    if (!DeleteItem(id))return false;
    gold += prize;
    return true;
}

void User::Use(int id) {
    auto it = std::find(use.begin(), use.end(), id);
    if (it != use.end())use.erase(it);
    else use.push_back(id);
}

bool User::AddSkill(int type) {
    if (skillPoints <= 0) return false;
    --skillPoints;
    ++skill[type];
    return true;
}


void User::Win() {
    ++wins;
    gold += 100;
    exp += 100;
    if (exp >= 1000) {
        ++level;
        skillPoints += 5;
        exp = 0;
    }
    clashId = -1;
}

std::string User::LoadUser() {
    return "du:" + name + ":" + std::to_string(level) + ":" + std::to_string(gold) + ":" + std::to_string(skillPoints)
           + ":" + std::to_string(skill[0]) + ":" + std::to_string(skill[1]) + ":" + std::to_string(skill[2]) + ":"
           + std::to_string(skill[3]) + ":" + std::to_string(wins) + ":" + std::to_string(loss) + ":" +
           std::to_string(exp) + ":;";
}

std::string User::LoadHave() {
    std::string s = std::accumulate(std::begin(have), std::end(have), std::string{},
                                    [](const std::string &a, int b) {
                                        return a.empty() ? std::to_string(b)
                                                         : a + ':' + std::to_string(b);
                                    });
    return "dh:" + s + ":;";
}

std::string User::LoadUse() {
    std::string s = std::accumulate(std::begin(use), std::end(use), std::string{},
                                    [](const std::string &a, int b) {
                                        return a.empty() ? std::to_string(b)
                                                         : a + ':' + std::to_string(b);
                                    });
    return "di:" + s + ":;";
}

std::string User::LoadInfo() {
    return name + ":" + std::to_string(level) + ":" + std::to_string(wins) + ":" + std::to_string(loss);
}

bool User::CheckClash(unsigned long clash) {
    return clash == clashId;
}
