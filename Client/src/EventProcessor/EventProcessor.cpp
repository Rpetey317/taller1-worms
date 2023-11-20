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

void EventProcessor::process_null(NullEvent& event) { /*std::cout << "Null event" << std::endl;*/
}

void EventProcessor::process_turn_update(TurnUpdate& event) {
    std::cout << "Now turn of player: " << event.get_id() << std::endl;
}

void EventProcessor::process_player_position(PlayerPosition& event) {
    std::cout << "Player " << event.get_id() << "with position: " << event.get_position_x() << ","
              << event.get_position_y() << std::endl;
}

void EventProcessor::process_map_update(MapUpdate& event) {
    std::cout << "Tengo que modiciar el atributo map de sdl y remplazarlo por el que contiene este "
                 "evento"
              << std::endl;
}

void EventProcessor::proccess_event(Event* event) { event->get_processed_by(*this); }

EventProcessor::~EventProcessor() {}
