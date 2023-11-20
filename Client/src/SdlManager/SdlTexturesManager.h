#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "../../../Common/CommonMapParser/CommonMapParser.h"
using namespace SDL2pp;  // NOLINT

//deberia ser map_textures_manager...
class SdlTexturesManager {

        public:
                SdlTexturesManager(Renderer& renderer, Window& window, std::string background_type);
                void draw(Tile& tile);
                void draw_background();

        private:
                Renderer& renderer;
                SDL_Rect src, dest;
                Window& window;
                Texture small_bridge;
                Texture large_bridge;
                Texture background;
                Texture water;
                


};
