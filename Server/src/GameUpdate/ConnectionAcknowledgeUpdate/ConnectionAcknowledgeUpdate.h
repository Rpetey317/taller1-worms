#ifndef __CONNECTIONACKUPDATE_H__
#define __CONNECTIONACKUPDATE_H__

#include "../GameUpdate.h"

class ConnectionAcknowledgeUpdate: public GameUpdate {
private:
    const int plid;

public:
    explicit ConnectionAcknowledgeUpdate(const int& plid);

    char get_sent_by(ServerProtocol& prot) override;

    const int& get_plid() const;

    ~ConnectionAcknowledgeUpdate() override = default;
};

#endif  // !__CONNECTIONACKUPDATE_H__
