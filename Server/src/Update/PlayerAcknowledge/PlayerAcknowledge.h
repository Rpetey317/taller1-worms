#ifndef __CONNECTIONACKUPDATE_H__
#define __CONNECTIONACKUPDATE_H__

#include "../Update.h"

class PlayerAcknowledge: public Update {
private:
    const int plid;

public:
    explicit PlayerAcknowledge(const int& plid);

    char get_sent_by(ServerProtocol& prot) override;

    int get_plid() const;

    ~PlayerAcknowledge() override = default;
};

#endif  // !__CONNECTIONACKUPDATE_H__
