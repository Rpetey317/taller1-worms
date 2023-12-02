#pragma once
#include <map>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;  // NOLINT

class SdlProjectilesTextureManager {

        public:
                explicit SdlProjectilesTextureManager(Renderer &renderer);
                //NECESITO UN DESTRUCTOR
                void render(std::string &projectile, int x_pos, int y_pos, int angle);


        private:
                std::map<std::string, Texture*> texture_map;
                Renderer &renderer;

};
