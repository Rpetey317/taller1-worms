#ifndef __CLIENT_NULL_UPDATE_H__
#define __CLIENT_NULL_UPDATE_H__

#include <memory>

#include "../Message.h"

class NullMessage: public Message {
public:
    NullMessage();
    ~NullMessage();

    bool is_valid() override;

    std::shared_ptr<GameUpdate> get_processed_by(Game& game) override;
};

#endif  // !__CLIENT_NULL_UPDATE_H__
