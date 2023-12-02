#ifndef __TIMERUPDATE_H__
#define __TIMERUPDATE_H__

#include "../Update.h"

class TimerUpdate: public Update {
    int time_left;
    int plid;

public:
    TimerUpdate(int time_left, int _id);
    ~TimerUpdate() = default;

    char get_sent_by(ServerProtocol& prot) override;

    int get_time_left() const;
    int get_plid() const;
};

#endif // !__TIMERUPDATE_H__
