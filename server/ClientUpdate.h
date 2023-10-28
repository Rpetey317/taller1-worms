#ifndef __CLIENTUPDATE_H__
#define __CLIENTUPDATE_H__

#include <string>

class ServerUpdate
{
private:
    const std::string msg;

public:
    ServerUpdate(std::string const& _msg);

    std::string get_msg() const;

    ~ServerUpdate(){}
};

#endif // !__CLIENTUPDATE_H__
