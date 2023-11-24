#ifndef __CLIENTPTURNADVANCEUPDATE_H__
#define __CLIENTPTURNADVANCEUPDATE_H__

#include <map>
#include <memory>

#include "../ClientUpdate.h"

class PlayerHandler;

class ClientPTurnAdvanceUpdate: public ClientUpdate {

    const std::map<int, std::unique_ptr<PlayerHandler>>::iterator& new_pl;

public:
    ClientPTurnAdvanceUpdate(const int& prev_pl_id,
                             const std::map<int, std::unique_ptr<PlayerHandler>>::iterator& new_pl);
    ~ClientPTurnAdvanceUpdate();

    bool is_valid() override;

    const std::map<int, std::unique_ptr<PlayerHandler>>::iterator& get_new_pl();

    GameUpdate* get_processed_by(GameHandler& game) override;
};

#endif  // !__CLIENTPTURNADVANCEUPDATE_H__
