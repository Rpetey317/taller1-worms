#ifndef PLAYERCONNECTED_H_
#define PLAYERCONNECTED_H_

#include <map>
#include <string>
#include <vector>

#include "../Event.h"

class PlayerConnected: public Event {
private:
    // std::string player_name;

public:
    explicit PlayerConnected(const int& player_id);

    void get_processed_by(EventProcessor& eventProcessor) override;

    bool is_new_player() override;

    // std::string get_player_name();
};

#endif  // PLAYERCONNECTEDEVENT_H_
