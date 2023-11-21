#include "ServerProtocol.h"

#include <iostream>

using namespace NetworkProtocol;  // NOLINT

char ServerProtocol::send_PlayerMessageUpdate(const GameChatMessageUpdate& upd) {
    // send code
    if (!this->send_char(MSGCODE_PLAYER_MESSAGE)) {
        return CLOSED_SKT;
    }

    // send player id
    if (!this->send_char((playerid_t)upd.get_plid())) {
        return CLOSED_SKT;
    }

    // send message
    if (!this->send_str(upd.get_msg())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_TurnChangeUpdate(const GameTurnChangeUpdate& upd) {
    // send code
    if (!this->send_char(MSGCODE_TURN_UPDATE)) {
        return CLOSED_SKT;
    }

    // send new current player id
    if (!this->send_char((playerid_t)upd.get_new_curr_player())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_ConnectionAcknowledgeUpdate(const GameAcknowledgeUpdate& upd) {
    // send code
    std::cout << "Sending ack" << std::endl;
    if (!this->send_char(MSGCODE_ACK)) {
        return CLOSED_SKT;
    }

    // send player id
    if (!this->send_char((playerid_t)upd.get_plid())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_PlayerDisconnectedUpdate(const GamePlayerDisconnectedUpdate& upd) {
    // send code
    if (!this->send_char(MSGCODE_PLAYER_DISCONNECT)) {
        return CLOSED_SKT;
    }

    // send player id
    if (!this->send_char((playerid_t)upd.get_player_id())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_PlayerConnectedUpdate(const GamePlayerConnectedUpdate& upd) {
    // send code
    std::cout << "Sending player connected" << std::endl; // Nunca se imprime. No llega a esta funcion
    if (!this->send_char(MSGCODE_PLAYER_CONNECT)) {
        return CLOSED_SKT;
    }

    // send player id
    if (!this->send_char((playerid_t)upd.get_player_id())) {
        return CLOSED_SKT;
    }
    std::cout << "Sent player connected" << std::endl;

    return SUCCESS;
}

char ServerProtocol::send_NullUpdate(const GameNullUpdate& upd) { return SUCCESS; }

char ServerProtocol::send_WorldUpdate(const GameWorldUpdate& upd) {
    // send code
    if (!this->send_char(MSGCODE_WORLD_UPD)) {
        return CLOSED_SKT;
    }
    if (!this->send_char((amount_players_t)upd.get_plcount())) {
        return CLOSED_SKT;
    }
    for (auto it = upd.begin(); it != upd.end(); ++it) {

        // send player id
        if (!this->send_char((playerid_t)it->first)) {
            return CLOSED_SKT;
        }

        // send position
        if (!this->send_point(it->second)) {
            return CLOSED_SKT;
        }
    }
    return SUCCESS;
}
