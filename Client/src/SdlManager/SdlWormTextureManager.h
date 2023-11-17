
#pragma once
#include <map>
#include <SDL2pp/SDL2pp.hh>



class SdlWormTextureManager {

        public:
                explicit SdlWormTextureManager(Renderer &renderer);
                //NECESITO UN DESTRUCTOR
                void render(int worm_state, int animation_phase, int x_pos, int y_pos, SDL_RendererFlip flip);


        private:
                std::map<std::string, Texture*> texture_map;
                Renderer &renderer;

};
