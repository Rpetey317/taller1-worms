#ifndef __TurnAdvance_H__
#define __TurnAdvance_H__

#include <memory>

#include "../Message.h"

class PlayerHandler;

class TurnAdvance: public Message {

    const int new_pl_id;

public:
    TurnAdvance(const int& prev_pl_id,
                const int& new_pl_id);
    ~TurnAdvance();

    bool is_valid() override;

    const int get_new_pl_id();

    std::shared_ptr<Update> get_processed_by(Game& game) override;
};

#endif  // !__TurnAdvance_H__
