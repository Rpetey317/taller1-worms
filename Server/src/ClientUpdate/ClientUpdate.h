#ifndef __CLIENTUPDATE_H__
#define __CLIENTUPDATE_H__

#include <string>

class ClientUpdate {
private:
    std::string msg;

public:
    explicit ClientUpdate(std::string const& _msg);

    ClientUpdate(): msg("") {}

    ClientUpdate& operator=(const ClientUpdate& other) {
        this->msg = other.msg;
        return *this;
    }

    std::string get_msg() const;

    ~ClientUpdate() {}
};

#endif  // !__CLIENTUPDATE_H__
