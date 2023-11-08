#ifndef __PLAYERMESSAGEUPDATE_H__
#define __PLAYERMESSAGEUPDATE_H__

#include <string>
#include <vector>

#include "../GameUpdate.h"

class PlayerMessageUpdate: public GameUpdate {
private:
    const std::string message;
    const int plid;

public:
    explicit PlayerMessageUpdate(const int& plid, std::string const& _msg);

    const std::string& get_msg() const;

    const int& get_plid() const;

    char get_sent_by(ServerProtocol& prot) override;
};


#endif  // !__PLAYERMESSAGEUPDATE_H__
