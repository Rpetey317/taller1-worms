#pragma once
#include <SDL2pp/SDL2pp.hh>
#include "CommonMapParser.h"
using namespace SDL2pp;  // NOLINT


class SdlTexturesManager {

        public:
                SdlTexturesManager(Renderer& renderer, Surface& small_bridge, Surface& large_bridge, Surface& water, Surface& background);
                void draw(Tile& tile);

        private:
                Renderer& renderer;
                SDL_Rect src, dest;
                Texture small_bridge;
                Texture large_bridge;
                Texture background;
                Texture water;


};
