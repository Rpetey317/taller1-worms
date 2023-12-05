#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "../../../Common/CommonMapParser/CommonMapParser.h"
using namespace SDL2pp;  // NOLINT

//deberia ser map_textures_manager...
class SdlTexturesManager {

        public:
                SdlTexturesManager(Renderer& renderer, Window& window, std::string background_type);
                void draw(Tile& tile, int camera_x, int camera_y);
                void draw_background();
                void update_background(std::string background_type);
                void draw_editor(Tile& tile, int camera_x, int camera_y);
                void draw_water(int camera_x, int camera_y);

        private:
                Renderer& renderer;
                SDL_Rect src, dest;
                Window& window;
                Texture small_bridge;
                Texture large_bridge;
                Texture* water1;
                Texture* water2;
                Texture* water3;
                Texture background;
                Texture* worm;
                int map_width;
                int map_height;
                


};
