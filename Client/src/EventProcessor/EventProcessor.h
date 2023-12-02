#ifndef EVENTPROCESSOR_H
#define EVENTPROCESSOR_H

#include <memory>
#include <string>

#include "../Event/EventHeaders.h"

class EventProcessor {
public:
    EventProcessor();

    /*
        Process methods for each type of event.
    */

    void process_connection(PlayerConnected& event);

    void process_msg(PlayerMessage& event);

    void process_disconnection(PlayerDisconnected& event);

    void process_null(NullEvent& event);

    void process_turn_update(TurnUpdate& event);

    void process_player_position(PlayerPosition& event);

    void process_map_update(MapUpdate& event);
    
    void proccess_proyectile_update(ProyectileUpdate& event);

    void proccess_event(std::shared_ptr<Event> event);


    ~EventProcessor();
};

#endif  // EVENTPROCESSOR_H
