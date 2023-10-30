#ifndef __GAMEUPDATE_H__
#define __GAMEUPDATE_H__

#include <string>
#include <vector>

#include "ServerProtocol.h"

class GameUpdate {
private:
    const std::string msg;  // to be removed

public:
    GameUpdate() = default;

    std::string get_msg() const;  // to be removed

    virtual char get_sent_by(ServerProtocol& prot) const = 0;

    virtual ~GameUpdate() = default;
};

#endif  // !__GAMEUPDATE_H__
