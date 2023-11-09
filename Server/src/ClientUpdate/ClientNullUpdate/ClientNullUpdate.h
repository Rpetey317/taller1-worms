#ifndef __CLIENT_NULL_UPDATE_H__
#define __CLIENT_NULL_UPDATE_H__

#include "../ClientUpdate.h"

class ClientNullUpdate : public ClientUpdate {
public:
    ClientNullUpdate();
    ~ClientNullUpdate();

    bool is_valid() override;

    GameUpdate* get_processed_by(GameHandler& game);
};

#endif // !__CLIENT_NULL_UPDATE_H__
