#include "JoinRequest.h"

#include <utility>

#include "LobbyHandlerThread.h"

JoinRequest::JoinRequest(std::string&& _name): name(std::move(_name)) {}

void JoinRequest::get_processed_by(LobbyHandlerThread& handler) { handler.join_game(*this); }

std::string& JoinRequest::get_name() const { return const_cast<std::string&>(name); }
