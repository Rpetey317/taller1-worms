#include "Game.h"

GameUpdate* GameHandler::process_disconnect(ClientDisconnectedUpdate& event) {
    this->players.erase(event.get_id());
    plcount--;
    std::cout << "A player disconnected. Now online: " << plcount << " players." << std::endl;
    return new GamePlayerDisconnectedUpdate(event.get_id());
}

GameUpdate* GameHandler::process_new_connect(ClientConnectedUpdate& event) {
    plcount++;
    std::cout << "New player connected. Now online: " << plcount << " players." << std::endl;
    return new GamePlayerConnectedUpdate(event.get_id());
}

GameUpdate* GameHandler::process_message(ClientMessageUpdate& event) {
    return new GameChatMessageUpdate(event.get_id(), event.get_msg());
}

GameUpdate* GameHandler::process_NullUpdate(ClientNullUpdate& event) {
    return new GameNullUpdate();
}
