#include "EventProcessor.h"

#include <iostream>

EventProcessor::EventProcessor() {}

void EventProcessor::process_connection(PlayerConnected& event) {
    std::cout << "Soy de tipo PlayerConnected" << std::endl;
}

void EventProcessor::process_msg(PlayerMessage& event) {
    std::cout << "Soy de tipo Message" << std::endl;    
    std::cout << event.get_msg() << std::endl;
}

void EventProcessor::process_disconnection(PlayerDisconnected& event) {
        std::cout << "Soy de tipo PlayerDisconnected" << std::endl;
}

void EventProcessor::proccess_event(Event* event) { event->get_processed_by(*this);}

EventProcessor::~EventProcessor() {}
