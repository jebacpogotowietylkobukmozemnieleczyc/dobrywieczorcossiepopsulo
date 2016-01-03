//
// Created by klimas on 28.11.15.
//

#ifndef TEST_USER_H
#define TEST_USER_H

#include <algorithm>
#include <iostream>
#include <vector>

class User {

private:
public:
    User(int id, const std::string &name, const std::string &password) : id(id), name(name), password(password),
                                                                         gold(100),
                                                                         loss(0), exp(0), level(1), skillPoints(5),
                                                                         logged(false), ready(false) {
        skill[0] = 1;
        skill[1] = 1;
        skill[2] = 1;
        skill[3] = 1;
    }


    //Item
    void AddItem(int id);
    void Use(int);
    bool DeleteItem(int id);
    bool SellItem(int id,int prize);

    //Skill
    bool AddSkill(int type);

    //Clash
    int getHp(){
        return level*100;
    }
    int getMp(){
        return level*50;
    }
    void Win();
    void Lose() { ++loss; }

    //Additional
    void Show() { std::cout << name << " " << password << std::endl; }

    //Login
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
    int skill[4];
    int wins;
    int loss;
    int exp;
    int level;
    int skillPoints;
    bool logged;
    bool ready;
    std::vector<int> use;
    std::vector<int> have;
    std::vector<int> skills;

};


#endif //TEST_USER_H
