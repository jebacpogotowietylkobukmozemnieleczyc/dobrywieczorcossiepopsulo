//
// Created by root on 22.11.15.
//

#include "Network.h"
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
void* Network::ClientLoop(void *arg){
    int nClientSocket = *((int *) arg);
    int n = 1;
    char buffer[n];
    int n2 = 5;
    char buffer2[n2] = "odpow";
    while (true) {
        int error = 0;
        socklen_t len = sizeof (error);
        int retval = getsockopt (nClientSocket, SOL_SOCKET, SO_ERROR, &error, &len);
        if(error!=0)break;
//        read(nClientSocket, buffer, n);
//        std::string string(buffer);
//        std::vector<std::string> x = split(string,':');
//        for (auto it = x.begin();  it != x.end() ; ++ it) {
//            std::cout << *it << std::endl;
//        }
////        write(1, buffer, n);
//        std::cout << "Size: " << x.size()  << std::endl;

        std::vector<std::string> x;
        std::string string;
        do{
            read(nClientSocket, buffer, n);
            if (buffer[0] == ':') {
                x.push_back(string);
                string.clear();
                continue;
            }
            string+=buffer[0];
        }while(buffer[0]!=';');
        for (auto it = x.begin();  it != x.end() ; ++ it) {
            std::cout << *it << std::endl;
        }
        std::cout << "Size: " << string  << std::endl;
        write(nClientSocket, buffer2,n2);
    }
    printf("close");
    close(nClientSocket);
    free(arg);
}

void Network::SetServer(char *argv[]) {
    /* address structure */
    memset(&stAddr, 0, sizeof(struct sockaddr));
    stAddr.sin_family = AF_INET;
    stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    stAddr.sin_port = htons(SERVER_PORT);

    /* create a socket */
    nSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (nSocket < 0)
    {
        fprintf(stderr, "%s: Can't create a socket.\n", argv[0]);
        exit(1);
    }
    setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nFoo, sizeof(nFoo));

    /* bind a name to a socket */
    nBind = bind(nSocket, (struct sockaddr*)&stAddr, sizeof(struct sockaddr));
    if (nBind < 0)
    {
        fprintf(stderr, "%s: Can't bind a name to a socket.\n", argv[0]);
        exit(1);
    }
    /* specify queue size */
    nListen = listen(nSocket, QUEUE_SIZE);
    if (nListen < 0)
    {
        fprintf(stderr, "%s: Can't set queue size.\n", argv[0]);
    }

    while(true) {

        nTmp = sizeof(struct sockaddr);
        int * nClientSocket = (int*) malloc(sizeof(int));

         *nClientSocket = accept(nSocket, (struct sockaddr*)&stClientAddr, &nTmp);
        pthread_t id;

        printf("%s: [connection from %s]\n",
               argv[0], inet_ntoa((struct in_addr)stClientAddr.sin_addr));

        pthread_create(&id, NULL, ClientLoop, (void *) nClientSocket);

    }

    close(nSocket);

}
auto Network::Login(std::string name, std::string password) {
    auto it = std::find_if(users.begin(),users.end(),[&name,&password](const  User& user){ return user.Login(name,password);});
    return it;
}

void Network::Initialise() {
    users.push_back(User(++userCount, "user", "12345"));
    users.push_back(User(++userCount, "user2", "1234"));

    //test
    auto it = Login("user2", "1234");
    if(it!=users.end()){
        it->Show();
    }
    else{
        std::cout << "lipa" << std::endl;
    }
    if (CreateAccount("user3", "123")) {
        it = Login("user3", "123");
        if(it!=users.end()){
            it->Show();
        }
        else{
            std::cout << "lipa" << std::endl;
        }
    }
    else{
        std::cout << "Nie zrobilo" << std::endl;
    }
    if (CreateAccount("user3", "123")) {
        it = Login("user3", "123");
        if(it!=users.end()){
            it->Show();
        }
        else{
            std::cout << "lipa" << std::endl;
        }
    }
    else{
        std::cout << "Nie zrobilo" << std::endl;
    }

}

bool Network::CreateAccount(std::string name, std::string password) {
    auto it = std::find_if(users.begin(),users.end(),[&name](const  User& user){ return user.CheckName(name);});
    if(it!=users.end())return false;
    users.push_back(User(++userCount, name, password));
    return true;
}
