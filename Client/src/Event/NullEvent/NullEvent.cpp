#include "NullEvent.h"

#include "../EventProcessor/EventProcessor.h"

NullEvent::NullEvent(const int& _id): Event(_id) {}

void NullEvent::get_processed_by(EventProcessor& eventProcessor) {
    eventProcessor.process_null(*this);
}
