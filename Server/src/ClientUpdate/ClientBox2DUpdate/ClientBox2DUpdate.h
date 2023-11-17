#ifndef __CLIENTBOX2DUPDATE_H__
#define __CLIENTBOX2DUPDATE_H__

#include "../ClientUpdate.h"

class ClientBox2DUpdate: public ClientUpdate {

    int command;

public:
    ClientBox2DUpdate(const int& id, const int& cmd);

    GameUpdate* get_processed_by(GameHandler& game) override;

    int& get_cmd();

    ~ClientBox2DUpdate() override = default;
};

#endif  // !__CLIENTBOX2DUPDATE_H__
