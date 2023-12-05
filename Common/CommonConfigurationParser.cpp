#include "CommonConfigurationParser.h"

#include <yaml-cpp/yaml.h>


CommonConfigurationParser::CommonConfigurationParser() {}

WeaponConfiguration CommonConfigurationParser::load_weapon(std::string weapon_name,
                                                           YAML::Node& config) {
    WeaponConfiguration weapon_config;

    weapon_config.damage = config[weapon_name]["damage"].as<int>();
    weapon_config.radius = config[weapon_name]["radius"].as<float>();
    weapon_config.ammount_of_bullets = config[weapon_name]["ammount_of_bullets"].as<int>();
    weapon_config.ammount_of_fragments = config[weapon_name]["ammount_of_fragments"].as<int>();
    weapon_config.radius_of_fragments = config[weapon_name]["radius_of_fragments"].as<float>();
    weapon_config.damage_of_fragments = config[weapon_name]["damage_of_fragments"].as<int>();
    weapon_config.restitution = config[weapon_name]["restitution"].as<float>();
    weapon_config.wind = config[weapon_name]["wind"].as<bool>();
    weapon_config.timer = config[weapon_name]["timer"].as<bool>();

    return weapon_config;
}

WeaponsConfiguration CommonConfigurationParser::get_weapons_configuration() {
    WeaponsConfiguration weapon_config;
    YAML::Node config;
    try {
        config = YAML::LoadFile("../config/WeaponsConfig.yaml");
    } catch (...) {
        return weapon_config;
    }
    weapon_config.air_strike = load_weapon("air_strike", config);
    weapon_config.baseball = load_weapon("baseball", config);
    weapon_config.dynamite = load_weapon("dynamite", config);
    weapon_config.holy_grenade = load_weapon("holy_grenade", config);
    weapon_config.green_grenade = load_weapon("green_grenade", config);
    weapon_config.red_grenade = load_weapon("red_grenade", config);
    weapon_config.mortar = load_weapon("mortar", config);
    weapon_config.banana = load_weapon("banana", config);
    weapon_config.bazooka = load_weapon("bazooka", config);
    return weapon_config;
}

Box2DConfiguration CommonConfigurationParser::get_box2D_configuration() {
    Box2DConfiguration box2d_config;
    YAML::Node config;
    try {
        config = YAML::LoadFile("../config/Box2DConfig.yaml");
    } catch (...) {
        return box2d_config;
    }

    box2d_config.deg_to_rad = config["deg_to_rad"].as<float>();
    box2d_config.rad_to_deg = config["rad_to_deg"].as<float>();

    box2d_config.meters_to_pixel = config["meters_to_pixel"].as<float>();
    box2d_config.pixel_to_meters = config["pixel_to_meters"].as<float>();
    box2d_config.map_height = config["map_height"].as<float>();
    box2d_config.map_width = config["map_width"].as<float>();
    box2d_config.gravity = config["gravity"].as<float>();
    box2d_config.velocity_iterations = config["velocity_iterations"].as<float>();
    box2d_config.position_iterations = config["position_iterations"].as<float>();
    box2d_config.time_step = config["time_step"].as<float>();
    box2d_config.timer = config["timer"].as<int>();

    return box2d_config;
}

WormConfiguration CommonConfigurationParser::get_worm_configuration() {
    WormConfiguration worm_config;
    YAML::Node config;
    try {
        config = YAML::LoadFile("../config/WormConfig.yaml");
    } catch (...) {
        return worm_config;
    }

    worm_config.health = config["health"].as<int>();
    worm_config.speed = config["speed"].as<float>();

    return worm_config;
}
