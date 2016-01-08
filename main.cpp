#include "Network.h"

int main(int argc, char *argv[]) {
    Network network;
    network.Initialise();
    network.SetServer(argv);
    return (0);
}