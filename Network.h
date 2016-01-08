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

class Network;

struct ThreadArgs {
    Network *network;
    int *nClientSocket;

};

class Network {
public:

    Network();

    void *ClientLoop(int *arg);

    static void *ClientLoopStatic(void *arg);

    void SetServer(char *argv[]);

    void Initialise();

    std::vector<std::shared_ptr<User> >::iterator Login(std::string name, std::string password);

    bool CreateAccount(std::string name, std::string password);

    std::string getReady(std::vector<std::shared_ptr<User> >::iterator &user);

    bool AddChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name);

    bool FindChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name);

    bool FindClash(std::vector<std::shared_ptr<User> >::iterator &user, std::string name);

    std::string CheckChallenge(std::vector<std::shared_ptr<User> >::iterator &user);

    bool TakeChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name);

    void DeclineChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name);

    void DeleteClash(std::vector<std::shared_ptr<User> >::iterator &user);

private:
    ThreadArgs threadArgs;
    int nSocket;
    int nBind, nListen;
    int nFoo = 1;
    socklen_t nTmp;
    struct sockaddr_in stAddr, stClientAddr;
    std::vector<std::shared_ptr<User>> users;
    std::vector<Clash> clashes;
    std::vector<Challenge> challenges;
    unsigned userCount = 0;

    std::map<std::string, std::function<std::string(std::vector<std::shared_ptr<User> >::iterator &user,
                                                    const std::vector<std::string> &x)> > callbackMap;

};


#endif //TEST_NETWORK_H
