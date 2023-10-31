#ifndef CLIENTPROTOCOL_H
#define CLIENTPROTOCOL_H

#include "Socket.h"
#include <string>

class ClientProtocol {
private:
    Socket skt;
    bool isclosed;

public:
    explicit ClientProtocol(Socket&& skt);
    ~ClientProtocol();
};


#endif //THREADS_2023C1_MDAVIC0_CLIENT_H
