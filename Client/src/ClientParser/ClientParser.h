#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include <arpa/inet.h>

class ClientParser {
public:
    ClientParser();
    std::vector<std::variant<uint8_t, uint16_t>> parse_send_msg(std::string& command);
    ~ClientParser();
};

#endif  // PARSER_H
