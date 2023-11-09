#ifndef PLAYERDISCONNECTED_H_
#define PLAYERDISCONNECTED_H_

#include <string>
#include <vector>

#include "../Event.h"

class PlayerDisconnected: public Event {
private:
    // std::string player_name;

public:
    explicit PlayerDisconnected(const int& player_id);

    void get_processed_by(EventProcessor& eventProcessor) override;

    // std::string get_player_name();
};

#endif  // PLAYERDISCONNECTEDEVENT_H_
