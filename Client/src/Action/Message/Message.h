#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <vector>

#include "../Action.h"

class Message: public Action {
private:
    std::string msg;

public:
    explicit Message(const std::string& msg);

    char get_send_by(ClientProtocol& prot) override;

    std::string get_msg();
};

#endif  // MESSAGE_H_
