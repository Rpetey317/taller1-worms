#include <iostream>
#include <list>
#include <utility>

#include "Common/Socket/Socket.h"
#include "Common/queue.h"
#include "Server/src/AccepterThread/AccepterThread.h"
#include "Server/src/ClientUpdate/ClientUpdate.h"
#include "Server/src/Game/Game.h"
#include "Server/src/GameLoopThread/GameLoopThread.h"
#include "Server/src/PlayerListMonitor/PlayerListMonitor.h"
#include "Server/src/ServerProtocol/ServerProtocol.h"

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
    Queue<ClientUpdate> eventq;
    GameHandler clients(eventq);

    ServerAccepterThread acc_th(std::move(acc), clients);
    GameLoopThread gloop(eventq, clients);

    // Execution
    acc_th.start();
    gloop.start();

    char c = 0;
    while (c != 'q') {
        std::cin.get(c);
    }

    // Destruction
    clients.close();
    acc_th.end();
    acc_th.join();
    gloop.stop();
    gloop.join();

    return 0;
}
