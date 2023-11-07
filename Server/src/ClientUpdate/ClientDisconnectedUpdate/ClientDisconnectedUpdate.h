#ifndef __CLIENTDISCONNECTEDUPDATE_H__ 
#define __CLIENTDISCONNECTEDUPDATE_H__ 

#include "../ClientUpdate.h"

class ClientDisconnectedUpdate: public ClientUpdate {
    
public:
    ClientDisconnectedUpdate(const int& _id);

    GameUpdate* get_processed_by(GameHandler& game) override;

    ~ClientDisconnectedUpdate() override = default;
};

#endif // !__CLIENTDISCONNECTEDUPDATE_H__
