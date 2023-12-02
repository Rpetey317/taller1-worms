#include "TimerUpdate.h"

#include "ServerProtocol.h"

TimerUpdate::TimerUpdate(int _time_left, int _plid): time_left(_time_left), plid(_plid) {}

char TimerUpdate::get_sent_by(ServerProtocol& prot) { return prot.send_TimerUpdate(*this); }

int TimerUpdate::get_time_left() const { return time_left; }
int TimerUpdate::get_plid() const { return plid; }
