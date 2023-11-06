#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

#include "SdlManager.h"


using namespace SDL2pp;  // NOLINT

SdlWorm::SdlWorm(Texture& sprite): sprite(sprite) {
    x_pos = 0;
    y_pos = 0;
    animation_phase = 0;
}

void SdlWorm::next_animation() {
    animation_phase = animation_phase + 1;
    if (animation_phase == 6) {
        animation_phase = 0;
    }
}

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

bool SdlManager::main_loop(Renderer& renderer, SdlWorm& worm) {

    bool keep_playing = event_handler();  // si me tiro un escape el player, keep_playing sera
                                          // false, para el resto siempre true
    // esto por si quiero cerrar de una forma un poco mas "linda"
    update_screen(renderer, worm);

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
    SdlWorm worm(sprites);
    worm.x_pos = 50;
    worm.y_pos = 50;
    worm.animation_phase = 0;
    unsigned int prev_ticks = SDL_GetTicks();
    while (is_running) {
        unsigned int frame_ticks = SDL_GetTicks();
        unsigned int frame_delta = frame_ticks - prev_ticks;
        prev_ticks = frame_ticks;
        is_running = main_loop(renderer, worm);


        SDL_Delay(1);
    }
}

void SdlManager::update_screen(Renderer& renderer, SdlWorm& worm) {
    std::vector<float> val;
    positions.try_pop(val);
    int src_x = 0, src_y = 0;
    if (!val.empty()) {
        renderer.Clear();
        src_x = 0;
        src_y = 60;
        renderer.Copy(worm.sprite, Rect(src_x, src_y, 50, 50), Rect((int)val[0], val[1], 50, 50));

    } else {
        renderer.Clear();

        src_x = 0;
        src_y = 60 * worm.animation_phase;
        renderer.Copy(worm.sprite, Rect(src_x, src_y, 50, 50),
                      Rect(worm.x_pos, worm.y_pos, 50, 50));
        worm.next_animation();
    }

    renderer.Present();
}

int main() {
    Queue<int> commands;
    Queue<std::vector<float>> positions;
    SdlManager manager(commands, positions);

    manager.run();
}
