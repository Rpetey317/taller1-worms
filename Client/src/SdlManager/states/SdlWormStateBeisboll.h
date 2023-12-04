#pragma once



#include "SdlWormState.h"
using namespace SDL2pp;  // NOLINT

class SdlWormStateBeisboll : public SdlWormState {

        public:
                SdlWormStateBeisboll();
                void render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) override;
                bool is_at_max_animation_phase(int animation_phase) override;     
                bool is_in_gun_state() override;   
                bool reduce_ammo(std::map<std::string, int>& gun_ammo) override;
                bool has_ammo(std::map<std::string, int>& gun_ammo) override;
                int projectile_id() override;
};