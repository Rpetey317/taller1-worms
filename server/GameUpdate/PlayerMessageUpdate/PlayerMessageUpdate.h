#ifndef __PLAYERMESSAGEUPDATE_H__
#define __PLAYERMESSAGEUPDATE_H__

#include <string>
#include <vector>

#include "../GameUpdate.h"

class PlayerMessageUpdate: public GameUpdate {
    const std::string message;

public:
    explicit PlayerMessageUpdate(std::string const& _msg);

    char get_code() const override;

    std::vector<char> get_serialized_msg() const override;
};


#endif  // !__PLAYERMESSAGEUPDATE_H__
