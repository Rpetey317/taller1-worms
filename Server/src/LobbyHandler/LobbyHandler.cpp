#include "LobbyHandler.h"

// TODO: Rewrite like 99% of this lmao
/*
using NetworkProtocol::msgcode_t;
using NetworkProtocol::MSGCODE_CREATE_GAME;
using NetworkProtocol::MSGCODE_PLAYER_CONNECT_TO_GAME;
// Comentar create_LobbyHandler y join LobbyHandler para que compile

LobbyHandler::LobbyHandler(): code(0) {}

// Game* LobbyHandler::create_LobbyHandler(Queue<Message*>& client_queue) {
//     std::lock_guard< std::mutex> lock(m);
//     Game* new_game = new Game(client_queue, this->code);
//     this->code++;
//     this->games.push_back(new_game);
//     return new_game;
// }

// Game* LobbyHandler::join_LobbyHandler(int code, Queue<Message*>& client_queue) {
//     std::lock_guard< std::mutex> lock(m);
//     if ((int)code >= (int)this->games.size()) {
//         throw std::runtime_error("El codigo ingresado no pertenece a ninguna partida!");
//     }
//     this->games[(int)code]->add_new_player(client_queue);
//     return this->games[code];
// }


void LobbyHandler::add_player(Socket&& player) {
    
    msgcode_t request = this->prot.recv_request();
    if (request == MSGCODE_CREATE_GAME) {
        // Create game. Esto deberia ir en el constructor de GameHandler (?)

        GameHandler* new_game = create_LobbyHandler();
        new_game->add_player(std::move(player));
        std::cout << "Created match: " << std::to_string(this->code) << std::endl;
    } else if (request == MSGCODE_PLAYER_CONNECT_TO_GAME) {
        int code = this->prot.recv_join();

            // Agregar al jugador a la partida. Tmb en el GameHandler (?)
        GameHandler* game = this->games[code];
        game->add_player(std::move(player));
        std::cout << "Joined to match: " << std::to_string(code) << std::endl;        
        } else {
            throw std::runtime_error("Codigo de mensaje invalido!");
        }
}

void LobbyHandler::remove_disconnected() {}

LobbyHandler::~LobbyHandler() {
    for (auto i: this->games) {
        delete i;
    }
}
 */
