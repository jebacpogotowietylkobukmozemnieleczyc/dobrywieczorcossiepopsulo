#include "Network.h"

Network::Network() : callbackMap({{"si", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
    user = Login(x.at(0), x.at(1));
    if (user != users.end())return "yes:;";
    return "no:;";
}},
                                  {"ac", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      AddChallenge(user, x.at(0));
                                      return "yes:;";
                                  }},
                                  {"tc", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      if (TakeChallenge(user, x.at(0)))return "yes:;";
                                      return "no:;";
                                  }},
                                  {"cc", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) { return CheckChallenge(user); }},
                                  {"fc", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      if (FindClash(user, x.at(0)))
                                          return "yes:;";
                                      return "no:;";
                                  }},
                                  {"dc", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      DeclineChallenge(user, x.at(0));
                                      return "yes:;";
                                  }},
                                  {"at", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      clashes.at((*user)->getClashId()).Attack((*user), std::stoi(x.at(0)));
                                      return "yes:;";
                                  }},
                                  {"sm", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      clashes.at((*user)->getClashId()).SetMp((*user), std::stoi(x.at(0)));
                                      return "yes:;";
                                  }},
                                  {"ct", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      if (clashes.at((*user)->getClashId()).CheckTurn((*user)))return "yes:;";
                                      return "no;";
                                  }},
                                  {"cr", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      if (clashes.at((*user)->getClashId()).CheckRound(std::stoi(x.at(0))))
                                          return "yes:;";
                                      return "no;";
                                  }},
                                  {"ar", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      clashes.at((*user)->getClashId()).ActiveTurn((*user));
                                      return "yes:;";
                                  }},
                                  {"lc", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      return clashes.at((*user)->getClashId()).LoadData();
                                  }},
                                  {"ls", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      DeleteClash(user);
                                      (*user)->Lose();
                                      return "yes:;";
                                  }},
                                  {"wn", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) {
                                      DeleteClash(user);
                                      (*user)->Win();
                                      return "yes:;";
                                  }},
                                  {"lo", [](std::vector<std::shared_ptr<User> >::iterator &user,
                                            const std::vector<std::string> &x) {
                                      (*user)->Logout();
                                      return "yes:;";
                                  }},
                                  {"sl", [](std::vector<std::shared_ptr<User> >::iterator &user,
                                            const std::vector<std::string> &x) {
                                      if ((*user)->SellItem(std::stoi(x.at(0)), std::stoi(x.at(1))))return "yes:;";
                                      return "no:;";
                                  }},
                                  {"ui", [](std::vector<std::shared_ptr<User> >::iterator &user,
                                            const std::vector<std::string> &x) {
                                      (*user)->Use(std::stoi(x.at(0)));
                                      return "yes:;";
                                  }},
                                  {"di", [](std::vector<std::shared_ptr<User> >::iterator &user,
                                            const std::vector<std::string> &x) {
                                      if ((*user)->DeleteItem(std::stoi(x.at(0))))return "yes:;";
                                      return "no:;";
                                  }},
                                  {"as", [](std::vector<std::shared_ptr<User> >::iterator &user,
                                            const std::vector<std::string> &x) {
                                      if ((*user)->AddSkill(std::stoi(x.at(0))))return "yes:;";
                                      return "no:;";
                                  }},
                                  {"sr", [](std::vector<std::shared_ptr<User> >::iterator &user,
                                            const std::vector<std::string> &x) {
                                      (*user)->setReady();
                                      return "yes";
                                  }},
                                  {"lu", [](std::vector<std::shared_ptr<User> >::iterator &user,
                                            const std::vector<std::string> &x) { return (*user)->LoadUser(); }},
                                  {"lh", [](std::vector<std::shared_ptr<User> >::iterator &user,
                                            const std::vector<std::string> &x) { return (*user)->LoadHave(); }},
                                  {"li", [](std::vector<std::shared_ptr<User> >::iterator &user,
                                            const std::vector<std::string> &x) { return (*user)->LoadUse(); }},
                                  {"lr", [&](std::vector<std::shared_ptr<User> >::iterator &user,
                                             const std::vector<std::string> &x) { return getReady(user); }}
                                 }) { }

void *Network::ClientLoop(int *arg) {
    int nClientSocket = *(arg);
    int n = 1;
    char buffer[n];
    std::vector<std::shared_ptr<User> >::iterator user;
    while (true) {
        int error = 0;
        socklen_t len = sizeof(error);
        getsockopt(nClientSocket, SOL_SOCKET, SO_ERROR, &error, &len);
        std::vector<std::string> x;
        std::string string;
        do {
            read(nClientSocket, buffer, n);
            if (buffer[0] == ':') {
                x.push_back(string);
                string.clear();
                continue;
            }
            string += buffer[0];
        } while (buffer[0] != ';');

        if (x.size() < 2)continue;
        std::string fn = x.at(1);
        std::string odp;
        std::vector<decltype(x)::value_type>(x.begin() + 2, x.end()).swap(x);
        try {
            odp = callbackMap.at(fn)(user, x);
        }
        catch (const std::out_of_range &) {
            std::cout << "Błędna funkcja." << std::endl;
        }
        write(nClientSocket, odp.c_str(), odp.size());
    }
    printf("close");
    close(nClientSocket);
    free(arg);
    return NULL;
}

void Network::SetServer(char *argv[]) {
    memset(&stAddr, 0, sizeof(struct sockaddr));
    stAddr.sin_family = AF_INET;
    stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    stAddr.sin_port = htons(SERVER_PORT);

    nSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (nSocket < 0) {
        fprintf(stderr, "%s: Can't create a socket.\n", argv[0]);
        exit(1);
    }
    setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char *) &nFoo, sizeof(nFoo));

    nBind = bind(nSocket, (struct sockaddr *) &stAddr, sizeof(struct sockaddr));
    if (nBind < 0) {
        fprintf(stderr, "%s: Can't bind a name to a socket.\n", argv[0]);
        exit(1);
    }
    nListen = listen(nSocket, QUEUE_SIZE);
    if (nListen < 0) {
        fprintf(stderr, "%s: Can't set queue size.\n", argv[0]);
    }

    while (true) {

        nTmp = sizeof(struct sockaddr);
        int *nClientSocket = (int *) malloc(sizeof(int));

        *nClientSocket = accept(nSocket, (struct sockaddr *) &stClientAddr, &nTmp);
        pthread_t id;

        printf("%s: [connection from %s]\n",
               argv[0], inet_ntoa((struct in_addr) stClientAddr.sin_addr));


        threadArgs.network = this;
        threadArgs.nClientSocket = nClientSocket;
        pthread_create(&id, NULL, &Network::ClientLoopStatic, &threadArgs);
    }
//    close(nSocket);
}

void *Network::ClientLoopStatic(void *arg) {
    ThreadArgs *threadArgs = (ThreadArgs *) arg;
    return (threadArgs->network)->ClientLoop(threadArgs->nClientSocket);
}

std::vector<std::shared_ptr<User> >::iterator Network::Login(std::string name, std::string password) {
    auto it = std::find_if(users.begin(), users.end(), [&name, &password](const std::shared_ptr<User> &user) {
        return user->Login(name, password);
    });
    if (it != users.end()) {
        (*it)->setLogged(true);
    }
    return it;
}

void Network::Initialise() {
    users.push_back(std::shared_ptr<User>(new User(++userCount, "User", "12345")));
    users.push_back(std::shared_ptr<User>(new User(++userCount, "User2", "12345")));

    users.at(0)->AddItem(0);
    users.at(0)->AddItem(1);
    users.at(0)->AddItem(2);
    users.at(0)->AddItem(3);

    users.at(1)->AddItem(0);
    users.at(1)->AddItem(1);
    users.at(1)->AddItem(2);
    users.at(1)->AddItem(3);


    users.at(0)->Use(0);
    users.at(0)->Use(2);

    users.at(1)->Use(1);
    users.at(1)->Use(3);

}

bool Network::CreateAccount(std::string name, std::string password) {
    auto it = std::find_if(users.begin(), users.end(),
                           [&name](const std::shared_ptr<User> &user) { return user->CheckName(name); });
    if (it != users.end())return false;
    users.push_back(std::shared_ptr<User>(new User(++userCount, name, password)));
    return true;
}

std::string Network::getReady(std::vector<std::shared_ptr<User> >::iterator &user) {
    std::vector<std::shared_ptr<User>> readyUsers;
    std::copy_if(users.begin(), users.end(), std::back_inserter(readyUsers),
                 [&user](const std::shared_ptr<User> &tuser) { return tuser->isReady() && (*user) != tuser; });
    std::string s = std::accumulate(std::begin(readyUsers), std::end(readyUsers), std::string{},
                                    [](const std::string &a, const std::shared_ptr<User> &user) {
                                        return a.empty() ? user->LoadInfo()
                                                         : a + ':' + user->LoadInfo();
                                    });
    return "dr:" + s + ":;";
}

bool Network::AddChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name) {
    auto it = std::find_if(users.begin(), users.end(), [&name](const std::shared_ptr<User> &user) {
        return user->CheckName(name) && user->isReady();
    });
    if (it == users.end())return false;
    Challenge challenge((*user), (*it));
    if (std::find(challenges.begin(), challenges.end(), challenge) != challenges.end())return false;
    challenges.push_back(Challenge((*user), (*it)));
    return true;
}

bool Network::FindChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name) {
    auto it = std::find_if(users.begin(), users.end(),
                           [&name](const std::shared_ptr<User> &user) { return user->CheckName(name); });
    if (it == users.end())return false;
    Challenge challenge((*it), (*user));
    if (std::find(challenges.begin(), challenges.end(), challenge) == challenges.end())return false;
    challenges.erase(std::remove(challenges.begin(), challenges.end(), challenge), challenges.end());
    return true;
}

bool Network::TakeChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name) {
    if (!FindChallenge(user, name))return false;
    auto it = std::find_if(users.begin(), users.end(),
                           [&name](const std::shared_ptr<User> &user) { return user->CheckName(name); });
    if (it == users.end())return false;
    clashes.push_back(Clash((*user), (*it)));
    unsigned long clashId = clashes.size() - 1;
    (*user)->setReady();
    (*it)->setClashId(clashId);
    (*user)->setClashId(clashId);
    return true;
}

void Network::DeclineChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name) {
    if (!FindChallenge(user, name))return;
}

void Network::DeleteClash(std::vector<std::shared_ptr<User> >::iterator &user) {
    long part = std::count_if(users.begin(), users.end(), [&user](const std::shared_ptr<User> &user2) {
        return user2->CheckClash((*user)->getClashId());
    });
    if (part != 1)
        return;
    clashes.erase(
            std::remove_if(clashes.begin(), clashes.end(),
                           [&user](const Clash &clash) { return clash.CheckUser((*user)); }),
            clashes.end());
}

std::string Network::CheckChallenge(std::vector<std::shared_ptr<User> >::iterator &user) {
    auto it = std::find_if(challenges.begin(), challenges.end(),
                           [&user](const Challenge &challenge) { return challenge.getUsers()[1] == (*user); });
    if (it == challenges.end())return "no;";
    return "cc:" + (it->getUsers()[0])->getName() + ":;";
}

bool Network::FindClash(std::vector<std::shared_ptr<User> >::iterator &user, std::string name) {
    auto it = std::find_if(users.begin(), users.end(),
                           [&name](const std::shared_ptr<User> &user2) { return user2->CheckName(name); });
    if (it == users.end())return false;
    auto it2 = std::find_if(clashes.begin(), clashes.end(),
                            [&user, &it](const Clash &clash) { return clash.CheckUsers((*it), (*user)); });
    return !(it2 == clashes.end());
}
