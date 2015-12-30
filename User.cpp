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

void User::SellItem(int id, int prize) {
    if(!DeleteItem(id))return;
    gold+=prize;
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

std::string User::LoadUser() {
//    return std::basic_string<char, char_traits < _CharT>, allocator < _CharT >> ();
    return  "du:" + name + ":" + std::to_string(level) + ":" + std::to_string(gold) + ":" + std::to_string(skillPoints)
            +":" + std::to_string(skill[0]) + ":"+ std::to_string(skill[1]) + ":"+ std::to_string(skill[2]) + ":"
            + std::to_string(skill[3]) + ":"+ std::to_string(wins)+ ":"+ std::to_string(loss) + ":"+ std::to_string(exp) +";";
}

std::string User::LoadHave() {
    std::string s = std::accumulate(std::begin(have), std::end(have), std::string{},
                                    [](const std::string& a, int b) {
                                        return a.empty() ? std::to_string(b)
                                                         : a + ':' + std::to_string(b);
                                    });
    return "dh:" + s + ";";
}

std::string User::LoadUse() {
    std::string s = std::accumulate(std::begin(use), std::end(use), std::string{},
                                    [](const std::string& a, int b) {
                                        return a.empty() ? std::to_string(b)
                                                         : a + ':' + std::to_string(b);
                                    });
    return "du:" + s + ";";
}

std::string User::LoadInfo() {
    return   name + ":" + std::to_string(level) + ":" + std::to_string(wins) + ":" + std::to_string(loss);
}
