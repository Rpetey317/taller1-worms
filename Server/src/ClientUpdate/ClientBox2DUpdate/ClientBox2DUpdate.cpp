#include "ClientBox2DUpdate.h"

#include "Game.h"

ClientBox2DUpdate::ClientBox2DUpdate(const int& _id, const int& _cmd): ClientUpdate(_id), command(_cmd) {}

GameUpdate* ClientBox2DUpdate::get_processed_by(GameHandler& game){
    return GameHandler.process_box2d(*this);
}

int& ClientBox2DUpdate::get_cmd(){
    return this->command;
}

ClientBox2DUpdate::~ClientBox2DUpdate() override = default;