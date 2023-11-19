#ifndef EVENTPROCESSOR_H
#define EVENTPROCESSOR_H

#include <string>

#include "../Event/EventHeaders.h"

class EventProcessor {
public:
    EventProcessor();

    void process_connection(PlayerConnected& event);

    void process_msg(PlayerMessage& event);

    void process_disconnection(PlayerDisconnected& event);

    void process_null(NullEvent& event);

    void process_turn_update(TurnUpdate& event);

    void process_player_position(PlayerPosition& event);

    void process_map_update(MapUpdate& event);

    void proccess_event(Event* event);


    ~EventProcessor();
};

#endif  // EVENTPROCESSOR_H
