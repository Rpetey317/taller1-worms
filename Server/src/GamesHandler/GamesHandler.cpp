#include "GamesHandler.h"

// Comentar create_GamesHandler y join GamesHandler para que compile

GamesHandler::GamesHandler(): code(0) {}

// GameHandler* GamesHandler::create_GamesHandler(Queue<ClientUpdate*>& client_queue) {
//     std::lock_guard< std::mutex> lock(m);
//     GameHandler* new_game = new GameHandler(client_queue, this->code);
//     this->code++;
//     this->games.push_back(new_game);
//     return new_game;
// }

// GameHandler* GamesHandler::join_GamesHandler(int code, Queue<ClientUpdate*>& client_queue) {
//     std::lock_guard< std::mutex> lock(m);
//     if ((int)code >= (int)this->games.size()) {
//         throw std::runtime_error("El codigo ingresado no pertenece a ninguna partida!");
//     }
//     this->games[(int)code]->add_new_player(client_queue);
//     return this->games[code];
// }

GamesHandler::~GamesHandler() {
    for (auto i: this->games) {
        delete i;
    }
}
