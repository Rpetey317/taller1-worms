#include "NullRequest.h"

#include "LobbyHandlerThread.h"

NullRequest::NullRequest(): Request() {}

void NullRequest::get_processed_by(LobbyHandlerThread& handler) {
    handler.process_null_request(*this);
}
