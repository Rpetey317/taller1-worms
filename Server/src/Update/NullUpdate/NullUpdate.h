#ifndef __GAME_NULL_UPDATE_H__
#define __GAME_NULL_UPDATE_H__

#include "../Update.h"

class NullUpdate: public Update {
public:
    NullUpdate() = default;
    ~NullUpdate() = default;

    char get_sent_by(ServerProtocol& prot) override;
};

#endif  // !__GAME_NULL_UPDATE_H__
