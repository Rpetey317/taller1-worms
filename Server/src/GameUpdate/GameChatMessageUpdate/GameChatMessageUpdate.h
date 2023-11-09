#ifndef __PLAYERMESSAGEUPDATE_H__
#define __PLAYERMESSAGEUPDATE_H__

#include <string>
#include <vector>

#include "../GameUpdate.h"

class GameChatMessageUpdate: public GameUpdate {
private:
    const std::string message;
    const int plid;

public:
    explicit GameChatMessageUpdate(const int& plid, std::string const& _msg);

    const std::string& get_msg() const;

    const int& get_plid() const;

    char get_sent_by(ServerProtocol& prot) override;

    ~GameChatMessageUpdate() override;
};


#endif  // !__PLAYERMESSAGEUPDATE_H__
