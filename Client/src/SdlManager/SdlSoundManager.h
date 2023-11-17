#pragma once
#include <map>
#include <SDL2pp/SDL2pp.hh>


class SdlSoundManager {

        public:
                SdlSoundManager();
                void play_sound(std::string);
                void destroy();

        private:
                Mixer mixer;
                Music background_music;
                std::map<std::string, Chunk*> sound_map;
                
};
