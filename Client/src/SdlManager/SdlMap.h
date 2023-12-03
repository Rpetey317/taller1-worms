#pragma once
#include <SDL2pp/SDL2pp.hh>


#include "texture_sound_manager/SdlMapTexturesManager.h"

using namespace SDL2pp;  // NOLINT

class SdlMap {
public:
    SdlMap(SdlCamera& camera, std::vector<Tile> map, SdlTexturesManager& textures_manager);
    void update_map(std::vector<Tile> new_map);
    void update_background(std::string background_type);
    void draw_map();
    void save_to_file(std::string& map_name);
    std::vector<Tile> get_worms_positions();
    void render_one(Tile tile);
    void draw_editor_map();
    int get_amount_of_worms();

private:
    SdlCamera &camera;
    std::vector<Tile> map;
    SdlTexturesManager& textures_manager;
    

};
