#ifndef __PlayerConnected_H__
#define __PlayerConnected_H__

#include <memory>

#include "../Message.h"

class PlayerConnectedMessage: public Message {

public:
    explicit PlayerConnectedMessage(const int& _id);

    std::shared_ptr<Update> get_processed_by(Game& game) override;

    ~PlayerConnectedMessage() override = default;
};

#endif  // !__PlayerConnected_H__
