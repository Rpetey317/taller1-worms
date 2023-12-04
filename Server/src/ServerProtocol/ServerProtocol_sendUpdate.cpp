#include <iostream>

#include "ServerProtocol.h"

using namespace NetworkProtocol;  // NOLINT

char ServerProtocol::send_PlayerMessageUpdate(const ChatUpdate& upd) {
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

char ServerProtocol::send_TurnChangeUpdate(const TurnChange& upd) {
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

char ServerProtocol::send_ConnectionAcknowledgeUpdate(const PlayerAcknowledge& upd) {
    // send code
    if (!this->send_char(MSGCODE_ACK)) {
        return CLOSED_SKT;
    }

    // send player id
    if (!this->send_char((playerid_t)upd.get_plid())) {
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
    if (!this->send_char((playerid_t)upd.get_player_id())) {
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
    if (!this->send_char((playerid_t)upd.get_player_id())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_NullUpdate(const NullUpdate& upd) { return SUCCESS; }

char ServerProtocol::send_WorldUpdate(const WorldUpdate& upd) {
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
        if (!this->send_Worm(it->second)) {
            return CLOSED_SKT;
        }
    }

    if (!this->send_char((amount_players_t)upd.get_weaponscount())) {
        return CLOSED_SKT;
    }
    for (auto it = upd.begin_weapons(); it != upd.end_weapons(); ++it) {

        // send player id
        if (!this->send_char((playerid_t)it->first)) {
            return CLOSED_SKT;
        }

        // send position
        if (!this->send_weapon(it->second)) {
            return CLOSED_SKT;
        }
    }


    return SUCCESS;
}

char ServerProtocol::send_TimerUpdate(const TimerUpdate& upd) {
    // send code
    if (!this->send_char(SRV_TIMER_UPD)) {
        return CLOSED_SKT;
    }

    // send id of player w/ turn
    if (!this->send_char(upd.get_plid())) {
        return CLOSED_SKT;
    }

    // send time
    if (!this->send_char(upd.get_time_left())) {
        return CLOSED_SKT;
    }

    return SUCCESS;
}

char ServerProtocol::send_Start(const StartUpdate& upd) {
    // send code
    if (!this->send_char(SRV_START_GAME)) {
        return CLOSED_SKT;
    }
    return SUCCESS;
}
