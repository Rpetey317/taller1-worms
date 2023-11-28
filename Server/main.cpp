#include <iostream>
#include <list>
#include <utility>

#include "AccepterThread.h"
#include "Game.h"
#include "GameLoopThread.h"
#include "Message.h"
#include "ServerProtocol.h"
#include "Socket.h"
#include "queue.h"

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
    Queue<std::shared_ptr<Message>> eventq(10000);
    Game game(eventq);

    ServerAccepterThread acc_th(std::move(acc), game);
    GameLoopThread gloop(eventq, game);

    // Execution
    acc_th.start();
    // gloop.start();

    char c = 0;
    while (c != 'q') {
        std::cin.get(c);
    }

    // Destruction
    game.close();
    acc_th.end();
    acc_th.join();
    // gloop.stop();
    // gloop.join();

    return 0;
}
