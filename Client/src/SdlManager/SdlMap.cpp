#include "SdlMap.h"
#include <fstream>
#include <yaml-cpp/yaml.h>
SdlMap::SdlMap(SdlCamera& camera, std::vector<Tile> map, SdlTexturesManager& textures_manager) : camera(camera), map(map), textures_manager(textures_manager) {}

void SdlMap::update_map(std::vector<Tile> new_map) {
    map = new_map;
}

void SdlMap::save_to_file(std::string& map_name) {
}
void SdlMap::render_one(Tile tile) {
    textures_manager.draw_editor(tile, camera.get_x(), camera.get_y());
}

void SdlMap::draw_editor_map() {
    textures_manager.draw_background();
    textures_manager.draw_water(camera.get_x(), camera.get_y());
    for (auto& tile : map) 
            textures_manager.draw_editor(tile, camera.get_x(), camera.get_y());
        
}

void SdlMap::update_background(std::string background_type) {
    textures_manager.update_background(background_type);
}

void SdlMap::draw_map() {
    textures_manager.draw_background();
    textures_manager.draw_water(camera.get_x(), camera.get_y());
    for (auto& tile : map) 
        if (tile.type != 2) 
            textures_manager.draw(tile, camera.get_x(), camera.get_y());
    
        
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
