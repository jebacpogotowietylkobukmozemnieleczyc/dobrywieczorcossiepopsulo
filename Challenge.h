//
// Created by klimas on 06.12.15.
//

#ifndef TEST_CHALLENGE_H
#define TEST_CHALLENGE_H


#include <memory>
#include "User.h"


class Challenge {

public:
    Challenge(const std::shared_ptr<User> &user1,const std::shared_ptr<User> &user2) {
        users.at(0)=user1;
        users.at(1)=user2;
    }
private:
public:
    const std::array<std::shared_ptr<User>, 2> &getUsers() const {
        return users;
    }

private:
    std::array<std::shared_ptr<User>,2> users;
};


inline bool operator==(const Challenge& lhs, const Challenge& rhs){
    return lhs.getUsers().at(0) == rhs.getUsers().at(0) && lhs.getUsers().at(1) == rhs.getUsers().at(1);
}
inline bool operator!=(const Challenge& lhs, const Challenge& rhs){return !operator==(lhs,rhs);}

#endif //TEST_CHALLENGE_H
