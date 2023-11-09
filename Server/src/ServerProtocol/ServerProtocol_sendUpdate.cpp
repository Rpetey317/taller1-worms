#include "ServerProtocol.h"

using namespace NetworkProtocol;  // NOLINT

char ServerProtocol::send_PlayerMessageUpdate(const PlayerMessageUpdate& upd) {
    // send code
    if (!this->send_char(MSGCODE_PLAYER_MESSAGE)) {
        return CLOSED_SKT;
    }

    // send player id
    if (!this->send_char((playerid_t) upd.get_plid())) {
        return CLOSED_SKT;
    }

    // send message
    if (!this->send_str(upd.get_msg())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_TurnChangeUpdate(const TurnChangeUpdate& upd) {
    // send code
    if (!this->send_char(MSGCODE_TURN_UPDATE)) {
        return CLOSED_SKT;
    }

    // send new current player id
    if (!this->send_char((playerid_t) upd.get_new_curr_player())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_ConnectionAcknowledgeUpdate(const ConnectionAcknowledgeUpdate& upd) {
    // send code
    if (!this->send_char(MSGCODE_ACK)) {
        return CLOSED_SKT;
    }

    // send player id
    if (!this->send_char((playerid_t) upd.get_plid())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_PlayerDisconnectedUpdate(const PlayerDisconnectedUpdate& upd) {
    // send code
    if (!this->send_char(MSGCODE_PLAYER_DISCONNECT)) {
        return CLOSED_SKT;
    }

    // send player id
    if (!this->send_char((playerid_t) upd.get_player_id())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_PlayerConnectedUpdate(const PlayerConnectedUpdate& upd) {
    // send code
    if (!this->send_char(MSGCODE_PLAYER_CONNECT)) {
        return CLOSED_SKT;
    }

    // send player id
    if (!this->send_char((playerid_t) upd.get_player_id())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_NullUpdate(const GameNullUpdate& upd){
    return SUCCESS;
}
