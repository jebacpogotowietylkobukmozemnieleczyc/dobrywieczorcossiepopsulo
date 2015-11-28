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
    User(int id, const std::string &name, const std::string &password): id(id), name(name), password(password), gold(100),
                                          loss(0), exp(0), skillPoints(5){
        skill[0]=1;
        skill[1]=1;
        skill[2]=1;
        skill[3]=1;
    }

    bool Login(std::string name,std::string password)const;
    bool CheckName(std::string name_)const;
    void Show(){ std::cout << name << " " << password << std::endl;}
    void AddItem(int id );
    void Use(int);
    bool DeleteItem(int id);
    bool AddSkill(int type);

private:
    int id;
    std::string name;
    std::string password;
    int gold;
    int skill[4];
    int wins;
    int loss;
    int exp;
    int skillPoints;
    std::vector<int> use;
    std::vector<int> have;
    std::vector<int> skills;

};


#endif //TEST_USER_H
