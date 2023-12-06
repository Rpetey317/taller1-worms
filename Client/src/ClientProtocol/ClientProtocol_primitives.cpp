#include "ClientProtocol.h"

#include <arpa/inet.h>

bool ClientProtocol::send_short(const uint16_t& num) {
    uint16_t nnum = htons(num);
    this->skt.sendall(&nnum, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ClientProtocol::send_long(const uint32_t& num) {
    uint32_t nnum = htonl(num);
    this->skt.sendall(&nnum, sizeof(uint32_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ClientProtocol::send_char(const uint8_t& num) {
    this->skt.sendall(&num, 1, &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ClientProtocol::send_str(const std::string& str) {
    strlen_t len = htons(str.length());
    this->skt.sendall(&len, sizeof(strlen_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    this->skt.sendall(str.data(), str.length(), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

std::string ClientProtocol::recv_str() {
    std::string msg = "";
    strlen_t name_size;
    this->skt.recvall(&name_size, sizeof(strlen_t), &isclosed);
    if (this->isclosed) {
        return msg;
    }
    name_size = ntohs(name_size);
    std::vector<char> vname(name_size);
    this->skt.recvall(&vname[0], name_size, &isclosed);
    if (isclosed) {
        return msg;
    }
    std::string chatmsg(vname.begin(), vname.end());
    msg = chatmsg;
    return msg;
}
