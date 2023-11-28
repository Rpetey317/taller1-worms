#ifndef __PLAYERCONNECTEDUPDATE_H__
#define __PLAYERCONNECTEDUPDATE_H__

#include "../Update.h"

class PlayerConnectedUpdate: public Update {
private:
    const int player_id;

public:
    explicit PlayerConnectedUpdate(int _player_id);

    int get_player_id() const;

    char get_sent_by(ServerProtocol& prot) override;

    ~PlayerConnectedUpdate();
};

#endif  // !__PLAYERCONNECTEDUPDATE_H__
