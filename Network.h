//
// Created by root on 22.11.15.
//

#ifndef TEST_NETWORK_H
#define TEST_NETWORK_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#define SERVER_PORT 6067
#define QUEUE_SIZE 5

#include <string>
#include <sstream>
#include <vector>


#include <pthread.h>
#include <algorithm>
#include <iostream>
#include <memory>
#include <map>

#include "User.h"
#include "Clash.h"
#include "Challenge.h"

static int eldo = 0;

class Network {
    int nSocket;
    int nBind, nListen;
    int nFoo = 1;
    socklen_t nTmp;
    struct sockaddr_in stAddr, stClientAddr;
    std::vector<std::shared_ptr<User>> users;
    std::vector<Clash> clashes;
    std::vector<Challenge> challenges;
    unsigned userCount = 0;

    std::map<std::string, std::function<void(std::vector<std::shared_ptr<User> >::iterator  &user,const std::vector<std::string> &x)> > callbackMap;

public:
    Network() : callbackMap({{"si", [&](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) { user = Login(x.at(0),x.at(1)); }},
                             {"ac", [&](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {AddChallenge(user,x.at(0));}},
                             {"tc", [&](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {TakeChallenge(user,x.at(0));}},
                             {"dc", [&](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {DeclineChallenge(user,x.at(0));}},
                             {"at", [&](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {clashes.at((*user)->getClashId()).Attack((*user),std::stoi(x.at(0)));}},
                             {"sm", [&](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {clashes.at((*user)->getClashId()).SetMp((*user),std::stoi(x.at(0)));}},
                             {"ar", [&](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {clashes.at((*user)->getClashId()).ActiveTurn((*user));}},
                             {"ls", [&](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {(*user)->Lose();DeleteClash(user);}},
                             {"wn", [&](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {(*user)->Win();DeleteClash(user);}},
                             {"lo", [](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {(*user)->Logout();}},
                             {"sl", [](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {(*user)->SellItem(std::stoi(x.at(0)),std::stoi(x.at(1)));}},
                             {"ui", [](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {(*user)->Use(std::stoi(x.at(0)));}},
                             {"di", [](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {(*user)->DeleteItem(std::stoi(x.at(0)));}},
                             {"sr", [](std::vector<std::shared_ptr<User> >::iterator &user,const std::vector<std::string> &x) {(*user)->setReady();}}
                             }) { }

    static void *ClientLoop(void *arg);

    void SetServer(char *argv[]);

    void Initialise();

    std::vector<std::shared_ptr<User> >::iterator& Login(std::string name, std::string password);

    bool CreateAccount(std::string name, std::string password);

    std::string getReady();

    bool AddChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name);

    void SendChallange();

    bool CheckChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name);

    void AnswerChallange();

    void TakeChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name);

    void DeclineChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name);

    void DeleteClash(std::vector<std::shared_ptr<User> >::iterator &user);

};


#endif //TEST_NETWORK_H
