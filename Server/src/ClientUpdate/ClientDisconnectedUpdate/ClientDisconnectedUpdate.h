#ifndef __CLIENTDISCONNECTEDUPDATE_H__
#define __CLIENTDISCONNECTEDUPDATE_H__

#include <memory>

#include "../ClientUpdate.h"

class ClientDisconnectedUpdate: public ClientUpdate {

public:
    explicit ClientDisconnectedUpdate(const int& _id);

    std::shared_ptr<GameUpdate> get_processed_by(Game& game) override;

    ~ClientDisconnectedUpdate() override = default;
};

#endif  // !__CLIENTDISCONNECTEDUPDATE_H__
