//
// Created by klimas on 28.11.15.
//

#ifndef TEST_CLASH_H
#define TEST_CLASH_H

#include <vector>
#include "User.h"

class Clash {
    int hp;
    int hp2;
    int mp1;
    int mp2;
    User * user;
    User * user2;
    std::vector<bool> turn;
    std::vector<bool> turn2;
};


#endif //TEST_CLASH_H
