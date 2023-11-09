#ifndef PLAYERDISCONNECTED_H_
#define PLAYERDISCONNECTED_H_

#include <string>
#include <vector>

#include "../Event.h"

class PlayerDisconnected: public Event {
private:
    // std::string player_name;

public:
    PlayerDisconnected(const int& player_id);

    // std::string get_player_name();
};

#endif  // PLAYERDISCONNECTEDEVENT_H_