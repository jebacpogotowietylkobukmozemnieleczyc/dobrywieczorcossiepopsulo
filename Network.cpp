#include "Network.h"

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
            std::cout << fn << std::endl;
            odp = callbackMap.at(fn)(user, x);
        }
        catch (const std::out_of_range &) {
            std::cout << "" << std::endl;
        }
        for (auto it = x.begin();  it != x.end() ; ++ it) {
            std::cout << *it << std::endl;
        }
        (*user)->Show();
        std::cout << "Size: " << odp  << std::endl;
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
    users.push_back(std::shared_ptr<User>(new User(++userCount, "user", "12345")));
    users.push_back(std::shared_ptr<User>(new User(++userCount, "user2", "1234")));

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

    users.at(0)->AddSkill(0);
    users.at(0)->AddSkill(1);
    users.at(0)->AddSkill(2);
    users.at(0)->AddSkill(3);
    users.at(0)->AddSkill(4);

    users.at(1)->AddSkill(0);
    users.at(1)->AddSkill(1);
    users.at(1)->AddSkill(2);
    users.at(1)->AddSkill(3);
    users.at(1)->AddSkill(4);
//
//    try {
//        callbackmap.at("lo")(x);
//        callbackmap.at("cg")(x);
//    }
//    catch(const std::out_of_range&){
//        std::cout << "juz jest ciemno" << std::endl;
//    }

    //test


//    auto it = Login("user", "12345");
//    std::vector<std::shared_ptr<User> >::iterator it;
//    std::vector<std::shared_ptr<User> >::iterator it2;
//    std::shared_ptr<User> it;
//    std::shared_ptr<User> it2;
//    std::vector<std::string> x;
//    auto sm = [&it,&x](){callbackMap.at("lo")(it,x);};


//    x.push_back("user");
//    x.push_back("12345");
//    callbackMap.at("si")(it,x);
//    if(it!=users.end()){
//        (*it)->Show();
//    }
//    else{
//        std::cout << "lipa" << std::endl;
//    }
//
//    x.clear();
//    x.push_back("user2");
//    x.push_back("1234");
////    callbackMap.at("lo")(it,x);
//    callbackMap.at("si")(it2,x);
////    callbackMap.at("si")(it2,x);
//    if(it2!=users.end()){
//        (*it2)->Show();
//    }
//    else{
//        std::cout << "lipa2" << std::endl;
//    }
//
//
//    (*it2)->AddItem(4);
//    x.clear();
//    x.push_back("4");
//    callbackMap.at("ui")(it2,x);
//    std::cout << "check" << std::endl;
//
//    x.clear();
//    x.push_back("4");
//    x.push_back("150");
//    callbackMap.at("sl")(it2,x);
//    std::cout << "check2" << std::endl;
//
//    callbackMap.at("sr")(it2,x);
//    x.clear();
//    x.push_back("user2");
//    callbackMap.at("ac")(it,x);
//    callbackMap.at("ac")(it,x);
//    x.clear();
//    x.push_back("user");
//    callbackMap.at("tc")(it2,x);
//    callbackMap.at("tc")(it2,x);
//
//    x.clear();
//    x.push_back("593");
//    callbackMap.at("at")(it,x);
//    x.clear();
//    x.push_back("123123");
//    callbackMap.at("at")(it,x);
//    callbackMap.at("sm")(it,x);
//    x.clear();
//    x.push_back("908");
//    callbackMap.at("sm")(it,x);
//    callbackMap.at("ar")(it2,x);
//    callbackMap.at("at")(it2,x);
//    callbackMap.at("ar")(it,x);
//
//    callbackMap.at("wn")(it,x);
//    callbackMap.at("ls")(it2,x);
//
//    callbackMap.at("sr")(it,x);
//    x.clear();
//    x.push_back("user");
//    callbackMap.at("ac")(it2,x);
//    x.clear();
//    x.push_back("user2");
//    callbackMap.at("tc")(it,x);
//
//    std::cout << "check3 " << (*it)->getClashId() << " " << (*it2)->getClashId() <<std::endl;
//    std::cout << getReady() << std::endl;
//
//    std::cout << "check2 "  << (*it)->LoadUser() <<std::endl;
//
//
//    std::cout << "check2" <<(*it)->LoadHave()<< std::endl;
//
//
//    std::cout << "check2" <<(*it)->LoadUse()<< std::endl;


//    std::cout << "check2" << std::endl;
//    (*it2)->setReady();
//
//    AddChallenge(*it,"user2");
//    AddChallenge(*it,"user2");
//    TakeChallenge(*it2,"user");
//    int clashid = clashes.size()-1;
//
//    clashes.at(clashid).Attack(*it,10);
//    clashes.at(clashid).Attack(*it,30);
//    clashes.at(clashid).SetMp(*it,12);
//    clashes.at(clashid).SetMp(*it,62);
//    clashes.at(clashid).SetMp(*it,72);
//    clashes.at(clashid).ShowName();
//    clashes.at(clashid).Attack(*it2,10);
//    clashes.at(clashid).Attack(*it2,30);
//    clashes.at(clashid).Attack(*it2,50);
//    clashes.at(clashid).Attack(*it,55);
//    clashes.at(clashid).SetMp(*it,902);
//    clashes.at(clashid).SetMp(*it2,3372);
//    clashes.at(clashid).ShowName();
//
//    (*it)->Win();
//    (*it2)->Lose();
//
//    DeleteClash(*it2);
//    std::cout << "Delete First" << std::endl;
//    DeleteClash(*it);
//    std::cout << "Delete Second" << std::endl;


//    clashes.push_back(Clash((*it),users.at(1)));
//    clashes.at(0).ShowName();
//    getReady();
//    (*it)->setReady();
//    getReady();
//    (*it)->Logout();
//    getReady();
//    it = Login("user2", "1234");
//    if(it!=users.end()){
//        (*it)->Show();
//    }
//    else{
//        std::cout << "lipa2" << std::endl;
//    }
//    if (CreateAccount("user3", "123")) {
//        it = Login("user3", "123");
//        if(it!=users.end()){
//            (*it)->Show();
//        }
//        else{
//            std::cout << "lipa" << std::endl;
//        }
//    }
//    else{
//        std::cout << "Nie zrobilo" << std::endl;
//    }
//    if (CreateAccount("user3", "123")) {
//        it = Login("user3", "123");
//        if(it!=users.end()){
//            (*it)->Show();
//        }
//        else{
//            std::cout << "lipa" << std::endl;
//        }
//    }
//    else{
//        std::cout << "Nie zrobilo" << std::endl;
//    }

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
    return "dr:" + s + ";";
}

bool Network::AddChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name) {
    auto it = std::find_if(users.begin(), users.end(), [&name](const std::shared_ptr<User> &user) {
        return user->CheckName(name) && user->isReady();
    });
    if (it == users.end())return false;
    Challenge challenge((*user), (*it));
    if (std::find(challenges.begin(), challenges.end(), challenge) != challenges.end())return false;
    challenges.push_back(Challenge((*user), (*it)));
    std::cout << "Add Challange" << std::endl;
    return true;
    //todo sendChallange
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

void Network::TakeChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name) {
    if (!FindChallenge(user, name))return;
    std::cout << "Take Challange" << std::endl;
    auto it = std::find_if(users.begin(), users.end(),
                           [&name](const std::shared_ptr<User> &user) { return user->CheckName(name); });
    if (it == users.end())return;
    //todo memory
    clashes.push_back(Clash((*it), (*user)));
    unsigned long clashId = clashes.size() - 1;
    (*it)->setClashId(clashId);
    (*user)->setClashId(clashId);

    clashes.at(0).ShowName();
    //todo anserChallange
}

void Network::DeclineChallenge(std::vector<std::shared_ptr<User> >::iterator &user, std::string name) {
    if (!FindChallenge(user, name))return;
    std::cout << "Decline Challange" << std::endl;
}

void Network::DeleteClash(std::vector<std::shared_ptr<User> >::iterator &user) {
    clashes.erase(
            std::remove_if(clashes.begin(), clashes.end(),
                           [&user](const Clash &clash) { return clash.CheckUser((*user)); }),
            clashes.end());
}

std::string Network::CheckChallenge(std::vector<std::shared_ptr<User> >::iterator &user) {
    auto it = std::find_if(challenges.begin(), challenges.end(),
                           [&user](const Challenge &challenge) { return challenge.getUsers()[1]==(*user); });
    if (it == challenges.end())return "no;";
    return (it->getUsers()[0])->getName() + ";";
}

bool Network::FindClash(std::vector<std::shared_ptr<User> >::iterator &user, std::string name) {
    auto it = std::find_if(users.begin(), users.end(),
                           [&name](const std::shared_ptr<User> &user) { return user->CheckName(name); });
    if (it == users.end())return false;
    auto it2 = std::find_if(clashes.begin(), clashes.end(),
                           [&user,&it](const Clash &clash) { return clash.CheckUsers((*user),(*it)); });
    if (it2 == clashes.end())return false;
    return true;
}
