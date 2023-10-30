#ifndef __PLAYERMESSAGEUPDATE_H__
#define __PLAYERMESSAGEUPDATE_H__

#include <string>
#include <vector>

#include "GameUpdate.h"

class PlayerMessageUpdate: public GameUpdate {
private:
    const std::string message;

public:
    explicit PlayerMessageUpdate(std::string const& _msg);

    const std::string& get_msg() const;

    char get_sent_by(ServerProtocol& prot) const override;
};


#endif  // !__PLAYERMESSAGEUPDATE_H__
