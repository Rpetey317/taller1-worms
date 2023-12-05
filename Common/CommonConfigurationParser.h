#pragma once
#include <string>

#include <yaml-cpp/yaml.h>

struct Box2DConfiguration {
    float deg_to_rad;
    float rad_to_deg;
    float pixel_to_meters;
    float meters_to_pixel;

    float map_width;
    float map_height;
    float gravity;
    float velocity_iterations;
    float position_iterations;
    float time_step;
    int timer;
};

struct WormConfiguration {
    int health;
    int speed;
};

struct WeaponConfiguration {
    int damage;
    float radius;
    int ammount_of_bullets;
    int ammount_of_fragments;
    float radius_of_fragments;
    int damage_of_fragments;
    float restitution;
    bool wind;
    bool timer;
};

struct WeaponsConfiguration {
    WeaponConfiguration bazooka;
    WeaponConfiguration mortar;
    WeaponConfiguration banana;
    WeaponConfiguration red_grenade;
    WeaponConfiguration green_grenade;
    WeaponConfiguration holy_grenade;
    WeaponConfiguration air_strike;
    WeaponConfiguration baseball;
    WeaponConfiguration dynamite;
};

class CommonConfigurationParser {
public:
    CommonConfigurationParser();
    WeaponsConfiguration get_weapons_configuration();
    WormConfiguration get_worm_configuration();
    Box2DConfiguration get_box2D_configuration();

private:
    WeaponConfiguration load_weapon(std::string weapon_name, YAML::Node& config);
};
