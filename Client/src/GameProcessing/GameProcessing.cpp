#include "GameProcessing.h"

GameProcessing::GameProcessing(const char* hostname, const char* port):
        skt(Socket(hostname, port)), protocol(std::move(this->skt)), keep_talking(true) {}

void GameProcessing::run() {
    // Creo los threads sender y receiver pasandoles el protocolo y los corro
}

GameProcessing::~GameProcessing() {}
