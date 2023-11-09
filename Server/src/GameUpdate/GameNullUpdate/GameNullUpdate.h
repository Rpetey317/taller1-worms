#ifndef __GAME_NULL_UPDATE_H__
#define __GAME_NULL_UPDATE_H__

#include "../GameUpdate.h"

class GameNullUpdate : public GameUpdate {
public:
    GameNullUpdate() = default;
    ~GameNullUpdate() = default;

    char get_sent_by(ServerProtocol& prot) override;
};

#endif // !__GAME_NULL_UPDATE_H__
