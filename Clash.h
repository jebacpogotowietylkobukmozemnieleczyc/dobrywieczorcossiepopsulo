//
// Created by klimas on 28.11.15.
//

#ifndef TEST_CLASH_H
#define TEST_CLASH_H

#include <vector>
#include <array>
#include <functional>
#include <memory>


#include "User.h"

class Clash {
public:
    Clash(const std::shared_ptr<User> &user1,const std::shared_ptr<User> &user2) {
        //todo initialization list
        users.at(0)=user1;
        users.at(1)=user2;
        turn[0] = false;
        turn[1] = false;
        turnCount=0;
        hp1 = user1->getHp();
        hp2 = user2->getHp();
        mp1 = user1->getMp();
        mp2 = user2->getMp();

    }
    void ActiveTurn(const std::shared_ptr<User> &user);
    void Attack(const std::shared_ptr<User> &user,int newHp);
    void SetMp(const std::shared_ptr<User> &user,int newMp);
    void IncreaseTurn();
    std::string LoadData();
    bool CheckTurn(const std::shared_ptr<User> &user);
    bool CheckRound(int round);
    bool CheckUser(const std::shared_ptr<User> &user) const;
    bool CheckUsers(const std::shared_ptr<User> &user,const std::shared_ptr<User> &user2) const;

    void ShowName(){
        std::cout << "Clash" << std::endl;
        users.at(0)->Show();
        users.at(1)->Show();
        std::cout << turnCount << std::endl;
        std::cout << "End" << std::endl;
    }
private:
    int hp1;
    int hp2;
    int mp1;
    int mp2;
    std::array<std::shared_ptr<User>,2> users;
    std::array<bool,2> turn;
    int turnCount;
};


#endif //TEST_CLASH_H
