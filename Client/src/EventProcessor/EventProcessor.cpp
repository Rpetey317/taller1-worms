#include "EventProcessor.h"

#include <iostream>

EventProcessor::EventProcessor() {}

void EventProcessor::process_connection(PlayerConnected& event) {
    std::cout << "Player " << event.get_id() << " connected." << std::endl;
}

void EventProcessor::process_msg(PlayerMessage& event) {
    std::cout << "Player " << event.get_id() << " chat: " << event.get_msg() << std::endl;
}

void EventProcessor::process_disconnection(PlayerDisconnected& event) {
    std::cout << "Player " << event.get_id() << " disconnected." << std::endl;
}

void EventProcessor::process_null(NullEvent& event) { std::cout << "Null event" << std::endl; }

void EventProcessor::proccess_event(Event* event) { event->get_processed_by(*this); }

EventProcessor::~EventProcessor() {}
