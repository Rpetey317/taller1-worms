#include "SdlMap.h"

SdlMap::SdlMap(std::vector<Tile> map, SdlTexturesManager& textures_manager) : map(map), textures_manager(textures_manager) {}


void SdlMap::draw_map() {
        textures_manager.draw_background();
    for (auto& tile : map) 
        textures_manager.draw(tile);
}