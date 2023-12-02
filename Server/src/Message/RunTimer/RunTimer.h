#ifndef __RUNTIMER_H__
#define __RUNTIMER_H__

#include "../Message.h"

class RunTimer: public Message {
public:
    RunTimer(int _id);
    ~RunTimer() = default;

    std::shared_ptr<Update> get_processed_by(Game& game);
};

#endif // !__RUNTIMER_H__
