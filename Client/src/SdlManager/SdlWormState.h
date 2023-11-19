
#pragma once
#include <SDL2pp/SDL2pp.hh>
#include <map>
class SdlWormState {

        public:
                SdlWormState();
                virtual void render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) = 0;
                virtual bool is_at_max_animation_phase(int animation_phase) = 0;
                virtual ~SdlWormState();
};
