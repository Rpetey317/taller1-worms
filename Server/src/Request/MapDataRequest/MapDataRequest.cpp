#include "MapDataRequest.h"

#include "LobbyHandlerThread.h"

MapDataRequest::MapDataRequest(): Request() {}

void MapDataRequest::get_processed_by(LobbyHandlerThread& handler) { handler.send_map_data(*this); }
