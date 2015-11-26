//
// Created by root on 22.11.15.
//

#include <pthread.h>
#include "Network.h"
void* Network::ClientLoop(void *arg){

    /* block for connection request */

    int nClientSocket = *((int *) arg);
    char buffer[50];
    int n = 10;
//        n = sprintf(buffer, "%s\n", asctime(local));
//        n = sprintf(buffer, "%s\n", "helloziom");
    while (true) {
        int error = 0;
        socklen_t len = sizeof (error);
        int retval = getsockopt (nClientSocket, SOL_SOCKET, SO_ERROR, &error, &len);
        if(error!=0)break;

        read(nClientSocket, buffer, n);
        write(1, buffer, n);
        write(nClientSocket, buffer, n);
    }
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
