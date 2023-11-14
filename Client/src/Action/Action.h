#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <vector>

class ClientProtocol;

class Action {
private:
    /* data */
public:
    Action() = default;

    virtual char get_send_by(ClientProtocol& prot) = 0;

    virtual ~Action() = default;
};

#endif  // ACTION_H_
