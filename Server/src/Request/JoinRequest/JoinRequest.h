#ifndef __JOINREQUEST_H__
#define __JOINREQUEST_H__

#include <string>

#include "../Request.h"

class JoinRequest: public Request {
    std::string name;

public:
    explicit JoinRequest(std::string&& name);

    void get_processed_by(LobbyHandlerThread& handler) override;

    std::string& get_name() const;
};

#endif  // !__JOINREQUEST_H__
