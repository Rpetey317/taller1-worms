#pragma once
#include <SDL2pp/SDL2pp.hh>
#include <vector>
#include <string>
#include "SdlCamera.h"
#include "SdlMap.h"
#include "../../../Common/CommonMapParser/CommonMapParser.h"
using namespace SDL2pp;  // NOLINT

class MapEditor {

        public:
                MapEditor(std::string& map_name);
                void run();
                

        private:
                std::string& map_name;
                std::vector<Tile> map;
                Tile new_tile;
                int angle = 0;
                SdlCamera camera;
                int mouse_x = 0;
                int mouse_y = 0;
                int ammount_of_worms = 0;
                bool is_choosing = false;
                bool event_handler(SdlMap& sdl_map);
                bool main_loop(Renderer& renderer, SdlMap& sdl_map);
                void update_screen(Renderer& renderer, SdlMap& sdl_map);
                int map_height;
};