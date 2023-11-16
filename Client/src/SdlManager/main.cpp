#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

#include <unistd.h>
#include "SdlManager.h"
#define FPS 15


using namespace SDL2pp;  // NOLINT


CommonMapParser::CommonMapParser() {}

std::vector<Tile> CommonMapParser::get_map(std::string file_name) {

        std::fstream archivo(file_name);
        std::vector<Tile> map;
        char scape;
        char type = ' ';
        char angle[4];
        char pos_x[5];
        char pos_y[5];
        while(!archivo.eof()) {
            archivo.get(type);
            archivo.get(scape);
            archivo.get(angle[0]);
            archivo.get(angle[1]);
            archivo.get(angle[2]);
            angle[3] = 0;
            archivo.get(scape);
            archivo.get(pos_x[0]);
            archivo.get(pos_x[1]);
            archivo.get(pos_x[2]);
            archivo.get(pos_x[3]);
            pos_x[4] = 0;
            archivo.get(scape);
            archivo.get(pos_y[0]);
            archivo.get(pos_y[1]);
            archivo.get(pos_y[2]);
            archivo.get(pos_y[3]);
            pos_y[4] = 0;
            archivo.get(scape);
            Tile tile = {type, atoi(angle), atoi(pos_x), atoi(pos_y)};
            map.emplace_back(tile);
        }

    return map;
}




SdlMap::SdlMap(std::vector<Tile> map, SdlTexturesManager& textures_manager) : map(map), textures_manager(textures_manager) {}


SdlTexturesManager::SdlTexturesManager(Renderer& renderer, Surface& small_bridge, Surface& large_bridge, Surface& water, Surface& background) :
 renderer(renderer), small_bridge(renderer, small_bridge), large_bridge(renderer, large_bridge), water(renderer, water), background(renderer, background) {
    src.x = src.y = 0;
    src.h = dest.h = 19;
}

void SdlTexturesManager::draw(Tile& tile) {

    switch (tile.type) {
        case '0':
            src.w = dest.w = 64;
            dest.x = tile.pos_x;
            dest.y = tile.pos_y;
            renderer.Copy(small_bridge, src, dest, tile.angle, NullOpt, 0);
            break;
        case '1':
            src.w = dest.w = 128;
            dest.x = tile.pos_x;
            dest.y = tile.pos_y;
            renderer.Copy(large_bridge, src, dest, tile.angle, NullOpt, 0);
            break;
        default:
            break;
    }
    
}

void SdlMap::draw_map() {
    for (auto& tile : map) 
        textures_manager.draw(tile);
}

SdlWorm::SdlWorm(Texture& sprite): flip(SDL_FLIP_NONE), sprite(sprite) {
    x_pos = 0;
    y_pos = 0;
    animation_phase = 0;
    worm_state = 0;
}

void SdlWorm::next_animation() {
    if (worm_state == 0) {
        animation_phase = 0;
        return;
    }
    animation_phase = animation_phase + 1;
    if (animation_phase == 6) {
        animation_phase = 0;
    }
}

SdlManager::SdlManager(Queue<int>& commands, Queue<std::vector<int>>& positions):
        commands(commands), positions(positions) {
    // Initialize SDL library
    // SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    // Initialize SDL_ttf library
    SDLTTF ttf;
}

bool SdlManager::event_handler(SdlWorm& worm, SDL_AudioDeviceID device, uint8_t* waveStart,
                               uint32_t waveLength) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        } else if (event.type == SDL_KEYDOWN) {

            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: {
                    commands.push(0);
                    return false;
                }
                case SDLK_RIGHT: {
                    worm.worm_state = 1;
                    SDL_QueueAudio(device, waveStart, waveLength);
                    SDL_PauseAudioDevice(device, 0);
                    worm.flip = SDL_FLIP_HORIZONTAL;
                    commands.push(1);
                    break;
                }
                case SDLK_LEFT: {
                    worm.worm_state = 1;
                    SDL_QueueAudio(device, waveStart, waveLength);
                    SDL_PauseAudioDevice(device, 0);
                    worm.flip = SDL_FLIP_NONE;
                    commands.push(2);
                    break;
                } break;
            }

        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT: {
                    worm.worm_state = 0;
                    SDL_PauseAudioDevice(device, 1);
                    commands.push(3);
                }
                case SDLK_LEFT: {
                    worm.worm_state = 0;
                    SDL_PauseAudioDevice(device, 1);
                    commands.push(3);
                }

                break;
            }
        }
    }

    return true;
}

bool SdlManager::main_loop(Renderer& renderer, SdlWorm& worm, SdlMap& map, SDL_AudioDeviceID device,
                           uint8_t* waveStart, uint32_t waveLength) {

    bool keep_playing = event_handler(worm, device, waveStart,
                                      waveLength);  // si me tiro un escape el player, keep_playing
                                                    // sera false, para el resto siempre true
    // esto por si quiero cerrar de una forma un poco mas "linda"
    update_screen(renderer, worm, map);

    return keep_playing;
}

void SdlManager::run() {

    SDL_AudioDeviceID device;
    SDL_AudioSpec audioSpec;
    Uint8* waveStart;
    Uint32 waveLength;

    if (SDL_LoadWAV("../../../Images/tuki.wav", &audioSpec, &waveStart, &waveLength) == NULL)
        std::cout << "triste" << std::endl;

    device = SDL_OpenAudioDevice(nullptr, 0, &audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if (device == 0) {
        std::cout << SDL_GetError() << std::endl;
        std::cout << "re triste" << std::endl;
    }
    Mixer mixer(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    Music background_music("../../../Images/background.wav");
    Chunk sound_effect("../../../Images/tuki.wav");

    const int frame_delay = 1000 / FPS;
    bool is_running = true;
    Window window("PoC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                  SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_SOFTWARE);
    Surface image_floor1("../../../Images/TerrainSprites/bridge.png");
    image_floor1.SetColorKey(true, 0);
    Surface image_floor2("../../../Images/TerrainSprites/large-bridge.png");
    image_floor2.SetColorKey(true, 0);
    //Surface image_floor3("../Images/Terrain/Construction/bridge-r.png");
    //image_floor3.SetColorKey(true, 0);
    Surface image_water("../../../Images/Worms/wblink1.png");//cambiar por el de water xd
    Surface image_background("../../../Images/TerrainSprites/back1.png");

    SdlTexturesManager textures_manager(renderer, image_floor1, image_floor2, image_water, image_background);
    CommonMapParser parser;
    SdlMap map(parser.get_map("../../../maps/mapita.txt"), textures_manager);
    Surface image("../../../Images/Worms/wblink1.png");

    image.SetColorKey(true, SDL_MapRGB(image.Get()->format, 128, 128,
                                       192));  // los numeros magicos son el rgb del fondo Texture

    Texture sprites(renderer, image);
    SdlWorm worm(sprites);
    worm.x_pos = 50;
    worm.y_pos = 50;
    worm.animation_phase = 0;
    mixer.PlayMusic(background_music, -1);
    while (is_running) {
        uint32_t frame_start;
        uint32_t frame_time;
        frame_start = SDL_GetTicks();
        is_running = main_loop(renderer, worm, map, device, waveStart, waveLength);
        // sleep(1); conexion super lagueada
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time)
            SDL_Delay(frame_delay - frame_time);
    }
}

void SdlManager::update_screen(Renderer& renderer, SdlWorm& worm, SdlMap& map) {
    std::vector<int> val;
    positions.try_pop(val);
    int src_x = 0, src_y = 0;

    if (!val.empty()) {
        renderer.Clear();
        src_x = 0;
        src_y = 60;
        renderer.Copy(worm.sprite, Rect(src_x, src_y, 50, 50),
                      Rect((int)val[0], (int)val[1], 50, 50), 0, NullOpt, worm.flip);

    } else {
        renderer.Clear();

        map.draw_map();

        src_x = 0;
        src_y = 60 * worm.animation_phase;
        renderer.Copy(worm.sprite, Rect(src_x, src_y, 50, 50), Rect(worm.x_pos, worm.y_pos, 50, 50),
                      0, NullOpt, worm.flip);
        worm.next_animation();
    }

    renderer.Present();
}

int main() {
    Queue<int> commands;
    Queue<std::vector<int>> positions;

    SdlManager manager(commands, positions);

    manager.run();
}
