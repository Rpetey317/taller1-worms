#ifndef __CLIENTUPDATE_H__
#define __CLIENTUPDATE_H__

#include <string>

class ClientUpdate {
private:
    std::string msg;
    bool valid;

public:
    explicit ClientUpdate(std::string const& _msg);

    ClientUpdate(): msg(""), valid(false) {}

    ClientUpdate& operator=(const ClientUpdate& other) {
        this->msg = other.msg;
        this->valid = other.valid;
        return *this;
    }

    std::string get_msg() const;

    bool is_valid() { return this->valid; }

    ~ClientUpdate() {}
};

#endif  // !__CLIENTUPDATE_H__
