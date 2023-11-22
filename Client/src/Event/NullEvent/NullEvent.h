#ifndef __NULL_EVENT_H__
#define __NULL_EVENT_H__

#include "../Event.h"

class NullEvent: public Event {
public:
    explicit NullEvent(const int& _id);

    void get_processed_by(EventProcessor& eventProcessor) override;

    std::map<int, Vect2D> get_worm_positions() override;

    bool is_new_player() override;

    ~NullEvent() override = default;
};

#endif  // !__NULL_EVENT_H__
