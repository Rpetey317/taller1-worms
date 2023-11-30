#include <arpa/inet.h>

#include "ServerProtocol.h"

bool ServerProtocol::send_short(const uint16_t& num) {
    uint16_t nnum = htons(num);
    this->cli.sendall(&nnum, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ServerProtocol::send_long(const uint32_t& num) {
    uint32_t nnum = htonl(num);
    this->cli.sendall(&nnum, sizeof(uint32_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ServerProtocol::send_char(const uint8_t& num) {
    this->cli.sendall(&num, 1, &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ServerProtocol::send_str(const std::string& str) {
    strlen_t len = htons(str.length());
    this->cli.sendall(&len, sizeof(strlen_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    this->cli.sendall(str.data(), str.length(), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ServerProtocol::send_Vect2D(const Vect2D& pt) {
    if (!this->send_short(pt.x)) {
        return false;
    }
    if (!this->send_short(pt.y)) {
        return false;
    }
    return true;
}

bool ServerProtocol::recv_char(uint8_t& num) {
    this->cli.recvall(&num, 1, &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    return true;
}

bool ServerProtocol::recv_short(uint16_t& num) {
    this->cli.recvall(&num, sizeof(uint16_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    num = ntohs(num);
    return true;
}

bool ServerProtocol::recv_long(uint32_t& num) {
    this->cli.recvall(&num, sizeof(uint32_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    num = ntohl(num);
    return true;
}

bool ServerProtocol::recv_str(std::string& str) {
    strlen_t len;
    this->cli.recvall(&len, sizeof(strlen_t), &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    len = ntohs(len);
    std::vector<char> vstr(len);
    this->cli.recvall(&vstr[0], len, &this->isclosed);
    if (this->isclosed) {
        return false;
    }
    str = std::string(vstr.begin(), vstr.end());
    return true;
}
