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

#include "User.h"
static int eldo= 0;
class Network {
    int nSocket;
    int nBind, nListen;
    int nFoo = 1;
    socklen_t nTmp;
    struct sockaddr_in stAddr, stClientAddr;
    std::vector<User> users;
    unsigned userCount = 0;

public:
    static void*ClientLoop(void *arg);
    void SetServer(char *argv[]);
    void Initialise();
    auto Login(std::string name, std::string password);
    bool CreateAccount(std::string name, std::string password);

};


#endif //TEST_NETWORK_H
