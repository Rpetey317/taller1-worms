#ifndef __Update_H__
#define __Update_H__

#include <string>
#include <vector>

class ServerProtocol;

class Update {
private:
    /* data */

public:
    Update() = default;

    virtual char get_sent_by(ServerProtocol& prot) = 0;

    virtual ~Update() = default;
};

#endif  // !__Update_H__
