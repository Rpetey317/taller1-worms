#include "SdlMap.h"
#include <fstream>
#include <yaml-cpp/yaml.h>



namespace YAML {
template<>
struct convert<Tile> {
  static Node encode(const Tile& rhs) {
    Node node;
    node.push_back(rhs.pos_x);
    node.push_back(rhs.pos_y);
    node.push_back(rhs.angle);
    return node;
  }

  static bool decode(const Node& node, Tile& rhs) {
    if(!node.IsSequence() || node.size() != 3) {
      return false;
    }

    rhs.pos_x = node[0].as<int>();
    rhs.pos_y = node[1].as<int>();
    rhs.angle = node[2].as<int>();
    return true;
  }
};
}



SdlMap::SdlMap(SdlCamera& camera, std::vector<Tile> map, SdlTexturesManager& textures_manager) : camera(camera), map(map), textures_manager(textures_manager) {}

void SdlMap::update_map(std::vector<Tile> new_map) {
    map = new_map;
}

void SdlMap::save_to_file(std::string& map_name) {
        YAML::Emitter out_small;
        out_small << YAML::BeginMap;
        out_small << YAML::Key << "small_tiles" ;
        out_small << YAML::BeginSeq;
    for (auto& tile : map) {
        if (tile.type == '0') {
            out_small << YAML::BeginMap;
            out_small << YAML::Key << "pos_x" << YAML::Value << tile.pos_x;
            out_small << YAML::Key << "pos_y" << YAML::Value << tile.pos_y;
            out_small << YAML::Key << "angle" << YAML::Value << tile.angle;
            out_small << YAML::EndMap;
        }
    }
    out_small << YAML::EndSeq;
    out_small << YAML::EndMap;
    YAML::Emitter out_long;
    out_long << YAML::BeginMap;
    out_long << YAML::Key << "long_tiles" ;
    out_long << YAML::BeginSeq;
    for (auto& tile : map) {
        if (tile.type == '1') {
            out_long << YAML::BeginMap;
            out_long << YAML::Key << "pos_x" << YAML::Value << tile.pos_x;
            out_long << YAML::Key << "pos_y" << YAML::Value << tile.pos_y;
            out_long << YAML::Key << "angle" << YAML::Value << tile.angle;
            out_long << YAML::EndMap;
        }
    }
    out_long << YAML::EndSeq;
    out_long << YAML::EndMap;
    YAML::Emitter out_worms;
    out_worms << YAML::BeginMap;
    out_worms << YAML::Key << "worms" ;
    out_worms << YAML::BeginSeq;
    for (auto& tile : map) {
        if (tile.type == '2') {
            out_worms << YAML::BeginMap;
            out_worms << YAML::Key << "pos_x" << YAML::Value << tile.pos_x;
            out_worms << YAML::Key << "pos_y" << YAML::Value << tile.pos_y;
            out_worms << YAML::Key << "angle" << YAML::Value << tile.angle;
            out_worms << YAML::EndMap;
        }
    }
    out_worms << YAML::EndSeq;
    out_worms << YAML::EndMap;
    std::ofstream fout(map_name);
    std::string comando = "mv " + map_name + " ../Maps/" + map_name;
    fout << out_small.c_str() << std::endl << out_long.c_str() << std::endl << out_worms.c_str();
    std::system(comando.c_str());

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
    std::vector<Tile> worms_positions;
    for (auto& tile: map) {
        if (tile.type == WORM_TYPE) {
            worms_positions.emplace_back(tile);
        }
    }
    return worms_positions;
}
