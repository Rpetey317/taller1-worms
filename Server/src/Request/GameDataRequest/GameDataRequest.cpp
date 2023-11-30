#include "GameDataRequest.h"

#include "LobbyHandlerThread.h"

GameDataRequest::GameDataRequest(): Request() {}

void GameDataRequest::get_processed_by(LobbyHandlerThread& handler) {
    handler.send_game_data(*this);
}
