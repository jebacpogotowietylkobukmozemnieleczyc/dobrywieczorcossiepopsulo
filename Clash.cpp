#include "Clash.h"

void Clash::IncreaseTurn() {
    ++turnCount;
    turn[0]= false;
    turn[1]= false;
}

void Clash::ActiveTurn(const std::shared_ptr<User> &user) {
    if(users[0]==user)turn[0]=true;
    else if(users[1]==user)turn[1]=true;
    if(turn[0] && turn[1])IncreaseTurn();
}

std::string Clash::LoadData() {
//    std::cout << "Hp1: " << hp1 << "Hp2: " << hp2 << "Mp1: " << mp1 <<"Mp2: " << mp2 << std::endl;
    return  "dc:" + std::to_string(hp1) + ":" + std::to_string(hp2) + ":" + std::to_string(mp1) +":" + std::to_string(mp2) + ";";

}

bool Clash::CheckTurn(int userTurn) {
    if(turnCount>userTurn)return true;
    return false;
}

void Clash::Attack(const std::shared_ptr<User> &user, int newHp) {
    if(users[0]==user){
        if(turn[0])
            return;
        hp2= newHp;
        turn[0]=true;
    }
    else if(users[1]==user){
        if(turn[1])
            return;
        hp1= newHp;
        turn[1]=true;
    }
    if(turn[0] && turn[1])IncreaseTurn();
}

void Clash::SetMp(const std::shared_ptr<User> &user,int newMp) {
    if(users[0]==user){
        mp1= newMp;
    }
    else if(users[1]==user){
        mp2= newMp;
    }
}

bool Clash::CheckUser(const std::shared_ptr<User> &user) const {
    return user==users[0];
}

bool Clash::CheckUsers(const std::shared_ptr<User> &user, const std::shared_ptr<User> &user2) const {
    return user==users[0] && user2==users[1];
}
