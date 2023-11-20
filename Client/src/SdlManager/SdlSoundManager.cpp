#include "SdlSoundManager.h"

SdlSoundManager::SdlSoundManager() : mixer(44100, MIX_DEFAULT_FORMAT, 2, 2048), background_music("../Images/background.wav")
{
    mixer.PlayMusic(background_music, -1);
    sound_map["CHARGE"] = new Chunk("../Images/tuki.wav"); 
    sound_map["THROWING"] = new Chunk("../Images/charge.wav");
}

void SdlSoundManager::play_sound(std::string sound_to_play) {
try {

    mixer.PlayChannel(-1, *sound_map[sound_to_play], 0);
} catch (Exception& err) {
    mixer.HaltChannel(-1);  //si hay demasiados sonidos -> quitalos todos
}

}

void SdlSoundManager::destroy() {
    for (auto chunk : sound_map) {
        delete chunk.second;
    }
    
}
