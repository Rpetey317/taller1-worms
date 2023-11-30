#ifndef __REQUEST_H__
#define __REQUEST_H__

class LobbyHandlerThread;

class Request {
protected:
    Request() = default;

public:
    virtual void get_processed_by(class LobbyHandlerThread& handler) = 0;
    virtual ~Request() = default;
};

#endif  // !__REQUEST_H__
