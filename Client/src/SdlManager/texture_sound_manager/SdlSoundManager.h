#pragma once
#include <map>
#include <SDL2pp/SDL2pp.hh>
using namespace SDL2pp;  // NOLINT


class SdlSoundManager {

        public:
                SdlSoundManager();
                void play_sound(std::string sound_to_play);
                void destroy();

        private:
                Mixer mixer;
                Music background_music;
                std::map<std::string, Chunk*> sound_map;
                
};
