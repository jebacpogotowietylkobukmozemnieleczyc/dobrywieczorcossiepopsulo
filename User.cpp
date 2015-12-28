//
// Created by klimas on 28.11.15.
//

#include "User.h"

bool User::Login(std::string name_, std::string password_)const {
    if(name_==name && password_==password && !logged){
        return true;
    }
    return false;
}


bool User::CheckName(std::string name_) const {
    if(name_==name)return true;
    return false;
}

void User::AddItem(int id) {
    have.push_back(id);
}

bool User::DeleteItem(int id) {
    auto it =  std::find(have.begin(), have.end(), id);
    if (it != have.end()){
        have.erase(it);
        return true;
    }
    return false;
}

void User::Use(int id) {
    auto it =  std::find(use.begin(), use.end(), id);
    if (it != use.end())use.erase(it);
    else use.push_back(id);
}

bool User::AddSkill(int type) {
    if(skillPoints<=0) return false;
    --skillPoints;
    ++skill[type];
}


void User::Win() {
    ++wins;
    gold+=100;
    exp+=100;
    if(exp>1000){
       ++level;
        skillPoints+=5;
        exp=0;
    }
}

