#ifndef __CONNECTIONACKUPDATE_H__
#define __CONNECTIONACKUPDATE_H__

#include "../GameUpdate.h"

class GameAcknowledgeUpdate: public GameUpdate {
private:
    const int plid;

public:
    explicit GameAcknowledgeUpdate(const int& plid);

    char get_sent_by(ServerProtocol& prot) override;

    int get_plid() const;

    ~GameAcknowledgeUpdate() override = default;
};

#endif  // !__CONNECTIONACKUPDATE_H__
