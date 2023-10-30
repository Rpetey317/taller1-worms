#ifndef __GAMEUPDATE_H__
#define __GAMEUPDATE_H__

#include <string>
#include <vector>

#include "ServerProtocol.h"

class GameUpdate {
private:
    const std::string msg;  // to be removed

public:
    GameUpdate() {}

    explicit GameUpdate(std::string const& _msg);

    std::string get_msg() const;  // to be removed

    virtual char get_sent_by(ServerProtocol& prot) const = 0;

    ~GameUpdate() {}
};

#endif  // !__GAMEUPDATE_H__
