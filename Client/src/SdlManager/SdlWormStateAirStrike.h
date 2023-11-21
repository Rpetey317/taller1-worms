#pragma once



#include "SdlWormState.h"
using namespace SDL2pp;  // NOLINT

class SdlWormStateAirStrike : public SdlWormState {

        public:
                SdlWormStateAirStrike();
                void render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) override;
                bool is_at_max_animation_phase(int animation_phase) override;   
                bool is_in_gun_state() override;     

};