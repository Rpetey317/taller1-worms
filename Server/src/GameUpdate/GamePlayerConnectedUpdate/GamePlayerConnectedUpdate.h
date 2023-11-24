#ifndef __PLAYERCONNECTEDUPDATE_H__
#define __PLAYERCONNECTEDUPDATE_H__

#include "../GameUpdate.h"

class GamePlayerConnectedUpdate: public GameUpdate {
private:
    const int player_id;

public:
    explicit GamePlayerConnectedUpdate(int _player_id);

    int get_player_id() const;

    char get_sent_by(ServerProtocol& prot) override;

    ~GamePlayerConnectedUpdate();
};

#endif  // !__PLAYERCONNECTEDUPDATE_H__
