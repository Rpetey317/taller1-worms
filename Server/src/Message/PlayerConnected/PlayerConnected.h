#ifndef __PlayerConnected_H__
#define __PlayerConnected_H__

#include <memory>

#include "../Message.h"

class PlayerConnected: public Message {

public:
    explicit PlayerConnected(const int& _id);

    std::shared_ptr<GameUpdate> get_processed_by(Game& game) override;

    ~PlayerConnected() override = default;
};

#endif  // !__PlayerConnected_H__
