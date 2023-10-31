#include "ClientProtocol.h"

ClientProtocol::ClientProtocol(Socket&& _srv): skt(std::move(_srv)), isclosed(false) {}

ClientProtocol::~ClientProtocol() {}