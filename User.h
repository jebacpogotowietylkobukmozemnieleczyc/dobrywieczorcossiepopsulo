#ifndef TEST_USER_H
#define TEST_USER_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

class User {
public:
    User(int id, const std::string &name, const std::string &password) : id(id), name(name), password(password),
                                                                         gold(100), wins(0),
                                                                         loss(0), exp(0), level(1), skillPoints(5),
                                                                         logged(false), ready(false) {
        skill.fill(1);
    }


    void AddItem(int id);

    void Use(int);

    bool CheckClash(unsigned long clash);

    bool DeleteItem(int id);

    bool SellItem(int id, int prize);

    bool AddSkill(int type);

    int getHp() {
        return level * 100;
    }

    int getMp() {
        return level * 50;
    }

    void Win();

    void Lose() {
        ++loss;
        clashId = -1;
    }

    bool Login(std::string name, std::string password) const;

    bool CheckName(std::string name_) const;

    void Logout() {
        ready = false;
        logged = false;
    }

    void setLogged(bool logged) {
        User::logged = logged;
    }

    void setReady() {
        ready = !ready;
    }

    bool isReady() const {
        return ready;
    }

    unsigned long getClashId() const {
        return clashId;
    }

    void setClashId(unsigned long clashId) {
        User::clashId = clashId;
    }

    const std::string &getName() const {
        return name;
    }

    std::string LoadUser();

    std::string LoadHave();

    std::string LoadUse();

    std::string LoadInfo();

private:
    int id;
    unsigned long clashId;
    std::string name;
    std::string password;
    int gold;
    std::array<int, 4> skill;
    int wins;
    int loss;
    int exp;
    int level;
    int skillPoints;
    bool logged;
    bool ready;
    std::vector<int> use;
    std::vector<int> have;
};


#endif //TEST_USER_H
