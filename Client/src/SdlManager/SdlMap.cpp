#include "SdlMap.h"

SdlMap::SdlMap(SdlCamera& camera, std::vector<Tile> map, SdlTexturesManager& textures_manager) : camera(camera), map(map), textures_manager(textures_manager) {}


void SdlMap::draw_map() {
        textures_manager.draw_background();
    for (auto& tile : map) 
        if (tile.type != 2) {
            textures_manager.draw(tile, camera.get_x(), camera.get_y());
        }
        
}

int SdlMap::get_amount_of_worms() {
    int counter = 0;
    for (auto& tile : map) {
        if (tile.type == WORM_TYPE)
            counter++;
    }
    return counter;
}

std::vector<Tile> SdlMap::get_worms_positions() {
    std::vector<Tile> worms_positions(get_amount_of_worms());
    for (auto& tile: map) {
        if (tile.type == WORM_TYPE) 
            worms_positions.emplace_back(tile);
    }
    return worms_positions;
}
