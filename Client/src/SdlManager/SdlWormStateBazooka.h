#pragma once



#include "SdlWormState.h"
using namespace SDL2pp;  // NOLINT

class SdlWormStateBazooka : public SdlWormState {

        public:
                SdlWormStateBazooka();
                void render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) override;
                bool is_at_max_animation_phase(int animation_phase) override;     

};