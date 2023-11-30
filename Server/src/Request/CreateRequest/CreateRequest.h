#ifndef __CREATEREQUEST_H__
#define __CREATEREQUEST_H__

#include <string>

#include "../Request.h"

class CreateRequest: public Request {
private:
    std::string game_name;
    std::string map_name;

public:
    CreateRequest(std::string&& game_name, std::string&& map_name);

    void get_processed_by(LobbyHandlerThread& handler) override;

    std::string& get_game_name() const;
    std::string& get_map_name() const;
};

#endif  // !__CREATEREQUEST_H__
