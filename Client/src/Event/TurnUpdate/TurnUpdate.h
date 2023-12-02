#ifndef __TURNUPDATE_H__
#define __TURNUPDATE_H__

#include <map>

#include "../Event.h"

class TurnUpdate: public Event {
public:
    explicit TurnUpdate(const int& player_id);

    void get_processed_by(EventProcessor& eventProcessor) override;

    ~TurnUpdate() = default;
};

#endif  // !__TURNUPDATE_H__
