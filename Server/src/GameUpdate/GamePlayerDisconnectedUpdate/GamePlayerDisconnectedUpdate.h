#ifndef __PLAYERDISCONNECTEDUPDATE_H__
#define __PLAYERDISCONNECTEDUPDATE_H__

#include "../GameUpdate.h"

class GamePlayerDisconnectedUpdate: public GameUpdate {
private:
    const int player_id;

public:
    explicit GamePlayerDisconnectedUpdate(int _player_id);

    int get_player_id() const;

    char get_sent_by(ServerProtocol& prot) override;

    ~GamePlayerDisconnectedUpdate();
};

#endif  // !__PLAYERDISCONNECTEDUPDATE_H__
