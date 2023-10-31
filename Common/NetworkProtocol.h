#ifndef __NETWORKPROTOCOL_H__
#define __NETWORKPROTOCOL_H__

#include <cstdint>

namespace NetworkProtocol {
// Message sending types
typedef uint16_t msglen_t;
typedef uint8_t msgcode_t;
typedef uint8_t playerid_t;

const msgcode_t MSGCODE_PLAYER_MESSAGE = 0x09;
const msgcode_t MSGCODE_PLAYER_CONNECT = 0x02;
const msgcode_t MSGCODE_PLAYER_DISCONNECT = 0x03;
const msgcode_t MSGCODE_TURN_UPDATE = 0x04;

}  // namespace NetworkProtocol

#endif  // !__NETWORKPROTOCOL_H__
