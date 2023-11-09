#ifndef __TURNCHANGEUPDATE_H__
#define __TURNCHANGEUPDATE_H__

#include "../GameUpdate.h"

class GameTurnChangeUpdate: public GameUpdate {
private:
    const int new_curr_player;

public:
    explicit GameTurnChangeUpdate(int& new_curr_player);

    char get_sent_by(ServerProtocol& prot) override;

    const int& get_new_curr_player() const;

    ~GameTurnChangeUpdate() override = default;
};

#endif  // !__TURNCHANGEUPDATE_H__
