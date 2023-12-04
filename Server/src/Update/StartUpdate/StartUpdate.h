#ifndef __STARTUPDATE_H__
#define __STARTUPDATE_H__

#include "../Update.h"

class StartUpdate: public Update {
    
public:
    StartUpdate();

    char get_sent_by(ServerProtocol& prot) override;

    ~StartUpdate();

};

#endif // !__STARTUPDATE_H__
