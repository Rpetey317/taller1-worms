#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

#include "SdlManager.h"

using namespace SDL2pp;  // NOLINT

SdlManager::SdlManager(Queue<int>& commands, Queue<std::vector<float>>& positions):
        commands(commands), positions(positions) {
    // Initialize SDL library
    SDL sdl(SDL_INIT_VIDEO);
    // Initialize SDL_ttf library
    SDLTTF ttf;
}

bool SdlManager::event_handler() {

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
                    commands.push(1);
                }
                case SDLK_LEFT: {
                    commands.push(2);
                } break;
            }

        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT: {
                    commands.push(3);
                }
                case SDLK_LEFT: {
                    commands.push(3);
                }

                break;
            }
        }
    }

    return true;
}

bool SdlManager::main_loop(Renderer& renderer, Texture& sprites) {

    bool keep_playing = event_handler();  // si me tiro un escape el player, keep_playing sera
                                          // false, para el resto siempre true
    // esto por si quiero cerrar de una forma un poco mas "linda"
    update_screen(renderer, sprites);

    return keep_playing;
}

void SdlManager::run() {

    bool is_running = true;
    Window window("PoC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                  SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_SOFTWARE);

    Surface image("../../../Images/Worms/wblink1.png");

    image.SetColorKey(true, SDL_MapRGB(image.Get()->format, 128, 128,
                                       192));  // los numeros magicos son el rgb del fondo Texture
                                               // sprites(renderer, image);

    Texture sprites(renderer, image);
    unsigned int prev_ticks = SDL_GetTicks();
    while (is_running) {
        unsigned int frame_ticks = SDL_GetTicks();
        unsigned int frame_delta = frame_ticks - prev_ticks;
        prev_ticks = frame_ticks;
        is_running = main_loop(renderer, sprites);


        SDL_Delay(1);
    }
}

void SdlManager::update_screen(Renderer& renderer, Texture& sprites) {
    std::vector<float> val;
    positions.try_pop(val);
    renderer.Clear();
    int src_x = 0, src_y = 0;

    src_x = 0;
    src_y = 60;
    if (!val.empty()) {
        renderer.Copy(sprites, Rect(src_x, src_y, 50, 50), Rect((int)val[0], val[1], 50, 50));
    }

    renderer.Copy(sprites, Rect(src_x, src_y, 50, 50), Rect(50, 50, 50, 50));

    renderer.Present();
}

int main() {
    Queue<int> commands;
    Queue<std::vector<float>> positions;
    SdlManager manager(commands, positions);

    manager.run();
}
