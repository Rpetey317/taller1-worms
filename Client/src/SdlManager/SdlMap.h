#pragma once
#include <SDL2pp/SDL2pp.hh>


#include "SdlTexturesManager.h"


using namespace SDL2pp;  // NOLINT

class SdlMap {
public:
    SdlMap(std::vector<Tile> map, SdlTexturesManager& textures_manager);

    void draw_map();
    std::vector<Tile> get_worms_positions();

private:
    std::vector<Tile> map;
    SdlTexturesManager& textures_manager;
    int get_amount_of_worms();
    

};
