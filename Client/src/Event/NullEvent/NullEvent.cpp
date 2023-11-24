#include "NullEvent.h"

#include "../EventProcessor/EventProcessor.h"

NullEvent::NullEvent(const int& _id): Event(_id) {}

void NullEvent::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_null(*this);
}

std::map<int, Vect2D> NullEvent::get_worm_positions() { return std::map<int, Vect2D>(); }

bool NullEvent::is_new_player() { return false; }
