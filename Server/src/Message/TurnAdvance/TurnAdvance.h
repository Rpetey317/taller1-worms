#ifndef __TurnAdvance_H__
#define __TurnAdvance_H__

#include <map>
#include <memory>

#include "../Message.h"

class PlayerHandler;

class TurnAdvance: public Message {

    const std::map<int, std::unique_ptr<PlayerHandler>>::iterator& new_pl;

public:
    TurnAdvance(const int& prev_pl_id,
                const std::map<int, std::unique_ptr<PlayerHandler>>::iterator& new_pl);
    ~TurnAdvance();

    bool is_valid() override;

    const std::map<int, std::unique_ptr<PlayerHandler>>::iterator& get_new_pl();

    std::shared_ptr<GameUpdate> get_processed_by(Game& game) override;
};

#endif  // !__TurnAdvance_H__
