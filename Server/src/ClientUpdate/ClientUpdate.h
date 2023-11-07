#ifndef __CLIENTUPDATE_H__
#define __CLIENTUPDATE_H__

#include <string>

// TODO: make this polymorphic
class ClientUpdate {
private:
    std::string msg;
    int id;
    bool valid;

public:
    explicit ClientUpdate(std::string const& _msg, const int& id);

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
