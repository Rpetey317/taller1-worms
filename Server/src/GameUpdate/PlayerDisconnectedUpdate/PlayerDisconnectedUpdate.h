#ifndef __PLAYERDISCONNECTEDUPDATE_H__
#define __PLAYERDISCONNECTEDUPDATE_H__

#include "../GameUpdate.h"

class PlayerDisconnectedUpdate: public GameUpdate {
private:
    const int player_id;

public:
    explicit PlayerDisconnectedUpdate(int _player_id);

    int get_player_id() const;

    char get_sent_by(ServerProtocol& prot) override;
};

#endif  // !__PLAYERDISCONNECTEDUPDATE_H__
