#ifndef PLAYERMESSAGE_H_
#define PLAYERMESSAGE_H_

#include <map>
#include <string>
#include <vector>

#include "../Event.h"

class PlayerMessage: public Event {
    // private:
    std::string msg;

public:
    PlayerMessage(const int& player_id, const std::string& msg);

    void get_processed_by(EventProcessor& eventProcessor) override;

    std::map<int, Vect2D> get_worm_positions() override;

    std::map<int, Worm> get_worms() override;

    bool is_new_player() override;

    std::string get_msg();
};

#endif  // PLAYERMESSAGE_H_
