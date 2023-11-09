#include "Game.h"

GameUpdate* GameHandler::process_disconnect(ClientDisconnectedUpdate& event) {
    this->plcount--;
    return new PlayerDisconnectedUpdate(event.get_id());
}

GameUpdate* GameHandler::process_new_connect(ClientConnectedUpdate& event) {
    this->plcount++;
    return new PlayerConnectedUpdate(event.get_id());
}

GameUpdate* GameHandler::process_message(ClientMessageUpdate& event) {
    return new PlayerMessageUpdate(event.get_id(), event.get_msg());
}

GameUpdate* GameHandler::process_NullUpdate(ClientNullUpdate& event) {
    return new GameNullUpdate();
}
