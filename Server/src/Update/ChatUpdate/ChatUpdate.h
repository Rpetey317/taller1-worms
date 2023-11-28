#ifndef __PLAYERMESSAGEUPDATE_H__
#define __PLAYERMESSAGEUPDATE_H__

#include <string>
#include <vector>

#include "../Update.h"

class ChatUpdate: public Update {
private:
    const std::string message;
    const int plid;

public:
    explicit ChatUpdate(const int& plid, std::string const& _msg);

    const std::string& get_msg() const;

    const int& get_plid() const;

    char get_sent_by(ServerProtocol& prot) override;

    ~ChatUpdate() override;
};


#endif  // !__PLAYERMESSAGEUPDATE_H__
