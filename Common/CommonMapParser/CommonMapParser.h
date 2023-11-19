#pragma once

#include <fstream>
#include <vector>
#include <string>

struct Tile {
        int type;
        int angle;
        int pos_x;
        int pos_y;
};

class CommonMapParser{
        public:
                CommonMapParser();
                std::vector<Tile> get_map(std::string file_name);
        private:


};
