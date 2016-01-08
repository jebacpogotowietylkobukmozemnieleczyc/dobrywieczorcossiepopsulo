#include "Challenge.h"

Challenge::Challenge(const std::shared_ptr<User> &user1, const std::shared_ptr<User> &user2) {
    users.at(0) = user1;
    users.at(1) = user2;
}
