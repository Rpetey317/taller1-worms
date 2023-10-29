#ifndef __GAMEUPDATE_H__
#define __GAMEUPDATE_H__

#include <string>
#include <vector>

class GameUpdate {
private:
    const std::string msg;

public:
    GameUpdate() {}

    explicit GameUpdate(std::string const& _msg);

    std::string get_msg() const;

    virtual char get_code() const = 0;

    virtual std::vector<char> get_serialized_msg() const = 0;

    ~GameUpdate() {}
};

#endif  // !__GAMEUPDATE_H__
