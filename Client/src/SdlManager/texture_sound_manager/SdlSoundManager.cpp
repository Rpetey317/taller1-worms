#include "SdlSoundManager.h"

SdlSoundManager::SdlSoundManager() : mixer(44100, MIX_DEFAULT_FORMAT, 2, 2048), background_music("../Images/background.wav")
{
    mixer.PlayMusic(background_music, -1);
    sound_map["BANANA_EXPLODING_SOUND"] = new Chunk("../Images/BANANA_EXPLODING.wav"); //en warap
    sound_map["MISSILE_EXPLODING_SOUND"] = new Chunk("../Images/EXPLOSION.wav");   //descargado
    sound_map["BEISBOLL_HIT_SOUND"] = new Chunk("../Images/BEISBOLL.wav");  //en warap
    sound_map["TELEPORT_SOUND"] = new Chunk("../Images/TELEPORT_SOUND.wav");    // descargado
    sound_map["HOLY_GRENADE_EXPLODING_SOUND"] = new Chunk("../Images/HOLY.wav");  // descargado
    sound_map["BAZOOKA_MORTAR_THROWING_SOUND"] = new Chunk("../Images/USING_LAUNCHER.wav"); // descargado
    sound_map["AIR_STRIKE_THROWING_SOUND"] = new Chunk("../Images/AIR_STRIKE_SOUND.wav"); //descargado

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
