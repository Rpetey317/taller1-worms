#ifndef __SERVERUPDATE_H__
#define __SERVERUPDATE_H__

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

#endif // !__SERVERUPDATE_H__
