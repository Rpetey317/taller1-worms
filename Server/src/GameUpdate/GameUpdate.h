#ifndef __GAMEUPDATE_H__
#define __GAMEUPDATE_H__

#include <string>
#include <vector>

class ServerProtocol;

class GameUpdate {
private:
    const std::string msg;  // to be removed

public:
    GameUpdate() = default;

    virtual char get_sent_by(ServerProtocol& prot) = 0;

    virtual ~GameUpdate() = default;
};

#endif  // !__GAMEUPDATE_H__
