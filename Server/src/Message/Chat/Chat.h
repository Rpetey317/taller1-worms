#ifndef __Chat_H__
#define __Chat_H__

#include <memory>
#include <string>

#include "../Message.h"

class Chat: public Message {
    std::string msg;

public:
    Chat(const int& _id, const std::string& _msg);

    std::shared_ptr<GameUpdate> get_processed_by(Game& game) override;

    std::string& get_msg();

    ~Chat() override = default;
};

#endif  // !__Chat_H__
