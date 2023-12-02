#ifndef __TIMER_H__
#define __TIMER_H__

#include <map>

#include "../Event.h"

class Timer: public Event {
private:
    int duration;
    // int worm_id;

public:
    explicit Timer(const int& player_id, int duration);

    void get_processed_by(EventProcessor& eventProcessor) override;

    int get_duration() override;

    ~Timer() = default;
};

#endif  // !__TIMER_H__
