#ifndef __PlayerDisconnected_H__
#define __PlayerDisconnected_H__

#include <memory>

#include "../Message.h"

class PlayerDisconnectedMessage: public Message {

public:
    explicit PlayerDisconnectedMessage(const int& _id);

    std::shared_ptr<Update> get_processed_by(Game& game) override;

    ~PlayerDisconnectedMessage() override = default;
};

#endif  // !__PlayerDisconnected_H__
