#ifndef __CLIENT_NULL_UPDATE_H__
#define __CLIENT_NULL_UPDATE_H__

#include <memory>

#include "../ClientUpdate.h"

class ClientNullUpdate: public ClientUpdate {
public:
    ClientNullUpdate();
    ~ClientNullUpdate();

    bool is_valid() override;

    std::shared_ptr<GameUpdate> get_processed_by(Game& game) override;
};

#endif  // !__CLIENT_NULL_UPDATE_H__
