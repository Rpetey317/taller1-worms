#include "Timer.h"

#include <map>

#include "../EventProcessor/EventProcessor.h"

Timer::Timer(const int& player_id, int duration): Event(player_id), duration(duration) {}

void Timer::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_timer(*this);
}

int Timer::get_duration() { return this->duration; }
