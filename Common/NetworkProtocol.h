#ifndef __NETWORKPROTOCOL_H__
#define __NETWORKPROTOCOL_H__

#include <cstdint>

namespace NetworkProtocol {
// Message sending types
typedef uint16_t strlen_t;
typedef uint16_t listlen_t;
typedef uint16_t point_t;
typedef uint8_t input_t;
typedef uint8_t msgcode_t;
typedef uint8_t playerid_t;
typedef uint8_t amount_players_t;
typedef uint8_t time_t;

// const msgcode_t MSGCODE_CREATE_GAME = 0x01;
// const msgcode_t MSGCODE_PLAYER_CONNECT_TO_GAME = 0x02;
const msgcode_t MSGCODE_ACK = 0x01;
const msgcode_t MSGCODE_PLAYER_CONNECT = 0x02;
const msgcode_t MSGCODE_PLAYER_DISCONNECT = 0x03;
const msgcode_t MSGCODE_TURN_UPDATE = 0x04;
const msgcode_t MSGCODE_PLAYER_AMOUNT = 0x06;
const msgcode_t MSGCODE_PLAYER_MOVE_RIGHT = 0x07;
const msgcode_t MSGCODE_PLAYER_MOVE_LEFT = 0x08;
const msgcode_t MSGCODE_PLAYER_MESSAGE = 0x09;

const msgcode_t MSGCODE_PLAYER_JUMP_FORWARD = 0x0A;
const msgcode_t MSGCODE_PLAYER_JUMP_BACKWARDS = 0x0B;
const msgcode_t MSGCODE_WORLD_UPD = 0x0C;
const msgcode_t MSGCODE_NULL_ACTION = 0x0D;
const msgcode_t MSGCODE_SHOOT = 0x14;

// New constant names from here on
const msgcode_t CLI_REQ_JOIN = 0x30;
const msgcode_t CLI_REQ_GAMES = 0x31;
const msgcode_t CLI_REQ_MAPS = 0x32;
const msgcode_t CLI_REQ_CREATE = 0x33;
const msgcode_t CLI_REQ_START = 0x34;

const msgcode_t SRV_RESP_GAMES = 0x20;
const msgcode_t SRV_RESP_MAPS = 0x21;
const msgcode_t SRV_SUCCESS = 0x22;
const msgcode_t SRV_FAIL = 0x23;
const msgcode_t SRV_START_GAME = 0x24;

const msgcode_t MSGCODE_PLAYER_POSITION = 0x15;
const msgcode_t MSGCODE_PROYECTILE_UPDATE = 0x16;
const msgcode_t MSGCODE_TIMER = 0x17;


// TODO: separar los msgcodes para los que se mandan del server al client y del client al server

// TODO: delete
const msgcode_t MSGCODE_BOX2D = 0xFF;
const msgcode_t SRV_TIMER_UPD = 0xA0;

const int ERROR = -1;
}  // namespace NetworkProtocol

#endif  // !__NETWORKPROTOCOL_H__
