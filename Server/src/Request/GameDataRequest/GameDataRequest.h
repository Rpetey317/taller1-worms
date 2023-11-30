#ifndef __GAMEDATAREQUEST_H__
#define __GAMEDATAREQUEST_H__

#include "../Request.h"

class GameDataRequest: public Request {
public:
    GameDataRequest();

    void get_processed_by(LobbyHandlerThread& handler) override;
};

#endif  // !__GAMEDATAREQUEST_H__
