#ifndef __NULLREQUEST_H__
#define __NULLREQUEST_H__

#include "../Request.h"

class NullRequest: public Request {
public:
    NullRequest();

    void get_processed_by(LobbyHandlerThread& handler) override;
};

#endif  // !__NULLREQUEST_H__
