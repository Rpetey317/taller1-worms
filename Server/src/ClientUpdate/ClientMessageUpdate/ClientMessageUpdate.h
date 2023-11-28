#ifndef __CLIENTMESSAGEUPDATE_H__
#define __CLIENTMESSAGEUPDATE_H__

#include <memory>
#include <string>

#include "../ClientUpdate.h"

class ClientMessageUpdate: public ClientUpdate {
    std::string msg;

public:
    ClientMessageUpdate(const int& _id, const std::string& _msg);

    std::shared_ptr<GameUpdate> get_processed_by(Game& game) override;

    std::string& get_msg();

    ~ClientMessageUpdate() override = default;
};

#endif  // !__CLIENTMESSAGEUPDATE_H__
