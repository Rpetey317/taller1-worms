#ifndef __PlayerDisconnected_H__
#define __PlayerDisconnected_H__

#include <memory>

#include "../Message.h"

class PlayerDisconnected: public Message {

public:
    explicit PlayerDisconnected(const int& _id);

    std::shared_ptr<GameUpdate> get_processed_by(Game& game) override;

    ~PlayerDisconnected() override = default;
};

#endif  // !__PlayerDisconnected_H__
