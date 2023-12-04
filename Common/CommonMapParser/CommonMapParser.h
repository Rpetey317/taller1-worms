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
    std::string get_background(std::string file_name);
    int get_amount_of_worms();
private:
    std::vector<Tile> map;
};
