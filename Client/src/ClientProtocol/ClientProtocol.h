#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <list>
#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "../Action/ActionHeaders.h"
#include "../Event/EventHeaders.h"

#include "NetworkProtocol.h"
#include "Socket.h"
#include "string"

using namespace NetworkProtocol;  // NOLINT

#define CLOSED_SKT -1
#define SUCCESS 0

/*
 * Wrapper class for client socket
 * Handles serialization and deserialization of messages
 */
class ClientProtocol {
private:
    Socket skt;
    bool isclosed;
    /*
     *  Primitive type send methods, to simplify update-specific send methods
     *  On successful send returns true, false if socket closed
     */
    bool send_short(const uint16_t& num);
    bool send_long(const uint32_t& num);
    bool send_char(const uint8_t& num);
    bool send_str(const std::string& str);

    /*
     * Primitive type recv methods, to simplify update-specific recv methods
     * Receiving status can be checked with this->isclosed
     */
    std::string recv_str();

    /*
        Receive methods of the diferent type of Events
     */

    /*
     *  Receive methods of the diferent type of Events
     */
    std::shared_ptr<Event> recv_player_connected();
    std::shared_ptr<Event> recv_player_message();
    std::shared_ptr<Event> recv_player_disconnected();
    std::shared_ptr<Event> recv_turn_update();
    std::shared_ptr<Event> recv_map_update();
    std::shared_ptr<Event> recv_player_position();
    std::shared_ptr<Event> recv_proyectile_update();
    std::shared_ptr<Event> recv_timer();

public:
    explicit ClientProtocol(Socket skt);
    playerid_t recv_player_id();

    /*
        Send methods for each type of action.
     */
    char send_Message(Message action);
    char send_Movement(Move action);
    char send_Jump(Jump action);
    char send_NullAction(NullAction action);
    char send_Shoot(Shoot action);
    char send_ChangeWeapon(ChangeWeapon action);

    std::list<std::string> req_map_info();
    std::list<std::string> req_game_info();
    bool req_succeed();
    char create_new_game(std::string& game_name, std::string& map_name);
    char join_game(std::string& game_name);
    char send_start_game();
    char recv_start_game();


    /*
        Sends code of match game
    */
    void send_code_game(size_t code);

    /*
        Receives the specific event update from the server
    */
    std::shared_ptr<Event> recv_update();

    /*
        Receives the code of the specific event update from the server
    */
    msgcode_t recv_code();

    /*
        Receives the amount of players in the game
    */
    int recv_amount_players();  // Not used. Could delete

    /*
        Closes socket
    */
    void close();

    ~ClientProtocol();
};

#endif  // PROTOCOL_H
