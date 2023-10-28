#include <iostream>
#include <list>
#include <utility>

#include "../common/common_socket.h"
#include "../common/queue.h"

#include "AccepterThread.h"
#include "Game.h"
#include "PlayerListMonitor.h"
#include "ServerProtocol.h"

#define EXPECTED_ARGC 2

int main(int argc, const char** argv) {
    // Args check
    if (argc == 1) {
        std::cout << "Format: ./server <port>\n"
                  << "<port>: Port to initialize server in\n";
        return 0;
    }

    if (argc != EXPECTED_ARGC) {
        std::cout << "ERROR: Expected " << EXPECTED_ARGC - 1 << " arguments, but received "
                  << argc - 1 << std::endl;
        return 1;
    }

    // Initialization
    Socket acc(argv[1]);
    ReceiverListMonitor recvers;
    GameHandler clients(recvers);
    ServerAccepterThread acc_th(std::move(acc), clients);

    // Execution
    acc_th.start();

    char c = 0;
    while (c != 'q') {
        std::cin.get(c);
    }

    // Destruction
    clients.close();
    acc_th.end();
    acc_th.join();

    return 0;
}
