#ifndef __NETWORKPROTOCOL_H__
#define __NETWORKPROTOCOL_H__

#include <cstdint>

namespace NetworkProtocol {
// Message sending types
typedef uint16_t strlen_t;
typedef uint8_t msgcode_t;
typedef uint8_t playerid_t;
typedef uint8_t amount_players_t;

// const msgcode_t MSGCODE_CREATE_GAME = 0x01;
// const msgcode_t MSGCODE_PLAYER_CONNECT_TO_GAME = 0x02;
const msgcode_t MSGCODE_ACK = 0x01;  // Que significa ACK?
const msgcode_t MSGCODE_PLAYER_CONNECT = 0x02;
const msgcode_t MSGCODE_PLAYER_DISCONNECT = 0x03;
const msgcode_t MSGCODE_TURN_UPDATE = 0x04;
const msgcode_t MSGCODE_PLAYER_AMOUNT = 0x06;
const msgcode_t MSGCODE_PLAYER_MESSAGE = 0x09;

const int ERROR = -1;
}  // namespace NetworkProtocol

#endif  // !__NETWORKPROTOCOL_H__
