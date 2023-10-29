#ifndef __GAMEUPDATE_H__
#define __GAMEUPDATE_H__

#include <string>

class GameUpdate {
private:
    const std::string msg;

public:
    explicit GameUpdate(std::string const& _msg);

    std::string get_msg() const;

    ~GameUpdate() {}
};

#endif  // !__GAMEUPDATE_H__
