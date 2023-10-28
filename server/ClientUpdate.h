#ifndef __CLIENTUPDATE_H__
#define __CLIENTUPDATE_H__

#include <string>

class ClientUpdate
{
private:
    const std::string msg;

public:
    ClientUpdate(std::string const& _msg);

    std::string get_msg() const;

    ~ClientUpdate(){}
};

#endif // !__CLIENTUPDATE_H__
