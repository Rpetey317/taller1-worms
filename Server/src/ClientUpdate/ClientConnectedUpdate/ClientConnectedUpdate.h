#ifndef __CLIENTCONNECTEDUPDATE_H__
#define __CLIENTCONNECTEDUPDATE_H__

#include "../ClientUpdate.h"

class ClientConnectedUpdate: public ClientUpdate {

public:
    explicit ClientConnectedUpdate(const int& _id);

    std::shared_ptr<GameUpdate> get_processed_by(GameHandler& game) override;

    ~ClientConnectedUpdate() override = default;
};

#endif  // !__CLIENTCONNECTEDUPDATE_H__
