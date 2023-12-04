#include "CreateRequest.h"

#include <utility>

#include "LobbyHandlerThread.h"

CreateRequest::CreateRequest(std::string&& _game_name, std::string&& _map_name):
        game_name(std::move(_game_name)), map_name(std::move(_map_name)) {}

void CreateRequest::get_processed_by(LobbyHandlerThread& handler) { handler.create_game(*this); }

std::string& CreateRequest::get_game_name() const { return const_cast<std::string&>(game_name); }

std::string& CreateRequest::get_map_name() const { return const_cast<std::string&>(map_name); }
