#include "CommonMapParser.h"

#include <stdlib.h>
#define VIGA_CORTA 0
#define VIGA_LARGA 1
#include <iostream>
#include <yaml-cpp/yaml.h>



CommonMapParser::CommonMapParser() {}

std::vector<Tile> CommonMapParser::get_map(std::string file_name) {

    std::vector<Tile> map;
    YAML::Node config = YAML::LoadFile("../maps/mapita.yaml");
    int x = 0;
    int y = 0;
    int angle = 0;
    YAML::Node small_tiles = config["small_tiles"];
    YAML::Node large_tiles = config["small_tiles"];
    YAML::Node worms_spawnpoints = config["worms"];
    for (YAML::const_iterator it = small_tiles.begin(); it != small_tiles.end(); ++it) {
        const YAML::Node& small_tile = *it;

        x = small_tile["x"].as<int>();
        y = small_tile["y"].as<int>();
        angle = small_tile["angle"].as<int>();
        std::cout << x << ":" << angle << ":" << y << std::endl;
        Tile tile = {'0', angle, x, y};
        map.emplace_back(tile);
    }

    for (YAML::const_iterator it = large_tiles.begin(); it != large_tiles.end(); ++it) {
        const YAML::Node& large_tile = *it;

        x = large_tile["x"].as<int>();
        y = large_tile["y"].as<int>();
        angle = large_tile["angle"].as<int>();
        std::cout << x << ":" << angle << ":" << y << std::endl;
        Tile tile = {'1', angle, x, y};
        map.emplace_back(tile);
    }

    for (YAML::const_iterator it = worms_spawnpoints.begin(); it != worms_spawnpoints.end(); ++it) {
        const YAML::Node& worm_spawnpoint = *it;

        x = worm_spawnpoint["x"].as<int>();
        y = worm_spawnpoint["y"].as<int>();
        angle = worm_spawnpoint["angle"].as<int>();
        std::cout << x << ":" << angle << ":" << y << std::endl;
        Tile tile = {'2', angle, x, y};
        map.emplace_back(tile);
    }

    return map;
}
