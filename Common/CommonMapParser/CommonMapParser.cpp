#include "CommonMapParser.h"

#include <stdlib.h>
#define VIGA_CORTA 0
#define VIGA_LARGA 1
#include <iostream>
#include <yaml-cpp/yaml.h>



CommonMapParser::CommonMapParser() {}

std::vector<Tile> CommonMapParser::get_map(std::string file_name) {

    std::vector<Tile> map;
    std::string path("../");
    path.append(file_name);
    YAML::Node config;
    try {
        config = YAML::LoadFile(path);
    } catch (...) {
        return map;
    }
    int x = 0;
    int y = 0;
    int angle = 0;
    YAML::Node small_tiles = config["small_tiles"];
    YAML::Node long_tiles = config["long_tiles"];
    YAML::Node worms_spawnpoints = config["worms"];
    for (YAML::const_iterator it = small_tiles.begin(); it != small_tiles.end(); ++it) {
        const YAML::Node& small_tile = *it;

        x = small_tile["pos_x"].as<int>();
        y = small_tile["pos_y"].as<int>();
        angle = small_tile["angle"].as<int>();
        Tile tile = {'0', angle, x, y};
        map.emplace_back(tile);
    }

    for (YAML::const_iterator it = long_tiles.begin(); it != long_tiles.end(); ++it) {
        const YAML::Node& long_tile = *it;

        x = long_tile["pos_x"].as<int>();
        y = long_tile["pos_y"].as<int>();
        angle = long_tile["angle"].as<int>();
        Tile tile = {'1', angle, x, y};
        map.emplace_back(tile);
    }

    for (YAML::const_iterator it = worms_spawnpoints.begin(); it != worms_spawnpoints.end(); ++it) {
        const YAML::Node& worm_spawnpoint = *it;

        x = worm_spawnpoint["pos_x"].as<int>();
        y = worm_spawnpoint["pos_y"].as<int>();
        angle = worm_spawnpoint["angle"].as<int>();
        Tile tile = {'2', angle, x, y};
        map.emplace_back(tile);
    }

    return map;
}
