
#pragma once
#include <SDL2pp/SDL2pp.hh>
#include <map>
#define AMMO_RENDER_SEPARATION 8
#define AMMO_RENDER_WIDTH 4
#define AMMO_RENDER_HEIGHT 20


using namespace SDL2pp;  // NOLINT

class SdlWormState {
        protected:
                bool is_animation_playing = false;

        public:
                bool just_choosen = false;
                SdlWormState();
                virtual void render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) = 0;
                virtual bool is_at_max_animation_phase(int animation_phase) = 0;
                virtual bool is_in_gun_state() = 0;
                virtual ~SdlWormState();
                virtual bool reduce_ammo(std::map<std::string, int>& gun_ammo) = 0;
                virtual bool has_ammo(std::map<std::string, int>& gun_ammo) = 0;
                virtual void play_animation() {is_animation_playing = true;};
                virtual void play_choosen_animation() {just_choosen = true;};
                virtual void render_ammo(Renderer& renderer, int ammount_of_bullets, int camera_x, int camera_y) {return;};
                virtual std::string get_name() {return "NULL";};
                virtual int projectile_id() {return -1;};
};
