#include "ClientProtocol.h"

#include <utility>

ClientProtocol::ClientProtocol(Socket&& _srv): skt(std::move(_srv)), isclosed(false) {}

ClientProtocol::~ClientProtocol() {}
