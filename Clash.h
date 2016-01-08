#ifndef TEST_CLASH_H
#define TEST_CLASH_H

#include <vector>
#include <array>
#include <functional>
#include <memory>


#include "User.h"

class Clash {
public:
    Clash(const std::shared_ptr<User> &user1, const std::shared_ptr<User> &user2);

    void ActiveTurn(const std::shared_ptr<User> &user);

    void Attack(const std::shared_ptr<User> &user, int newHp);

    void SetMp(const std::shared_ptr<User> &user, int newMp);

    void IncreaseTurn();

    std::string LoadData();

    bool CheckTurn(const std::shared_ptr<User> &user);

    bool CheckRound(int round);

    bool CheckUser(const std::shared_ptr<User> &user) const;

    bool CheckUsers(const std::shared_ptr<User> &user, const std::shared_ptr<User> &user2) const;

private:
    int turnCount;
    int hp1;
    int hp2;
    int mp1;
    int mp2;
    std::array<std::shared_ptr<User>, 2> users;
    std::array<bool, 2> turn;
};


#endif //TEST_CLASH_H
