#include "GameProcessing.h"

Client::Client(const char *hostname, const char *port):
                        skt(Socket(hostname, port)),
                        protocol(std::move(this->skt)),
                        keep_talking(true) {}

void Client::run() {
}

Client::~Client() {}
