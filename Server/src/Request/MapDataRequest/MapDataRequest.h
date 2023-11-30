#ifndef __MAPDATAREQUEST_H__
#define __MAPDATAREQUEST_H__

#include "../Request.h"

class MapDataRequest: public Request {
public:
    MapDataRequest();

    void get_processed_by(LobbyHandlerThread& handler) override;
};

#endif  // !__MAPDATAREQUEST_H__
