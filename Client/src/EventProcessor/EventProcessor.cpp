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
    // Vect2D position = event.get_position();
    // std::cout << "Player " << event.get_id() << "with position: " << position.x << "," <<
    // position.y
    //           << std::endl;
}

void EventProcessor::process_map_update(MapUpdate& event) {
    // std::cout << "Map update" << std::endl;
    // std::map<int, Vect2D> worm_positions = event.get_worm_positions();
    // for (auto& worm : worm_positions) {
    //     std::cout << "Player " << worm.first << " with position: " << worm.second.get_x() << ","
    //               << worm.second.get_y() << std::endl;
    // }
}

void EventProcessor::proccess_proyectile_update(ProyectileUpdate& event) {}

void EventProcessor::process_timer(Timer& event) {}

void EventProcessor::proccess_event(std::shared_ptr<Event> event) {
    event->get_processed_by(*this);
}


EventProcessor::~EventProcessor() {}
