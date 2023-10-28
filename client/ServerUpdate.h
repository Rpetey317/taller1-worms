#ifndef __SERVERUPDATE_H__
#define __SERVERUPDATE_H__

#include <string>

class ClientUpdate {
private:
    const std::string msg;

public:
    explicit ClientUpdate(std::string const& _msg);

    std::string get_msg() const;

    ~ClientUpdate() {}
};

#endif  // !__SERVERUPDATE_H__
