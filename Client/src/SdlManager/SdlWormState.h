
#pragma once
#include <SDL2pp/SDL2pp.hh>
#include <map>
using namespace SDL2pp;  // NOLINT

class SdlWormState {

        public:
                SdlWormState();
                virtual void render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) = 0;
                virtual bool is_at_max_animation_phase(int animation_phase) = 0;
                virtual bool is_in_gun_state() = 0;
                virtual ~SdlWormState();
                virtual bool reduce_ammo(std::map<std::string, int>& gun_ammo) = 0;
                virtual bool has_ammo(std::map<std::string, int>& gun_ammo) = 0;
};
