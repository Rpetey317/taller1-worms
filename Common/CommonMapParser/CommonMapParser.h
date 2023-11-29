#pragma once

#include <fstream>
#include <string>
#include <vector>
#define WORM_TYPE '2'

struct Tile {
    int type;
    int angle;
    int pos_x;
    int pos_y;
};

class CommonMapParser {
public:
    CommonMapParser();
    std::vector<Tile> get_map(std::string file_name);

private:
};
