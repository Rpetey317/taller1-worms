#ifndef __TURNCHANGEUPDATE_H__
#define __TURNCHANGEUPDATE_H__

#include "../Update.h"

class TurnChange: public Update {
private:
    const int new_curr_player;

public:
    explicit TurnChange(const int& new_curr_player);

    char get_sent_by(ServerProtocol& prot) override;

    const int& get_new_curr_player() const;

    ~TurnChange() override = default;
};

#endif  // !__TURNCHANGEUPDATE_H__
