#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

#include "SdlManager.h"


using namespace SDL2pp;  // NOLINT

SdlManager::SdlManager(Queue<int>& commands, Queue<float>& positions):
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
            return;
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

bool SdlManager::main_loop() {
    keep_playing = true;
    keep_playing = event_handler();  // si me tiro un escape el player, keep_playing sera false,
                                     // para el resto siempre true
    // esto por si quiero cerrar de una forma un poco mas "linda"
    update_screen();

    return keep_playing;
}

void SdlManager::run() {
    is_running = true;
    while (is_running) {
        // cosas para manejar el delta time...
        is_running = main_loop();
    }
}

void SdlManager::update_screen() {
    // aca tendria la queue que me patean los datos y tendria que actualizar la pantalla
}

int main() {

    SdlManager manager;

    manager.run();
}
/*


// Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
    Window window("SDL2pp demo",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_RESIZABLE);

    // Create accelerated video renderer with default driver
    Renderer renderer(window, -1, SDL_RENDERER_SOFTWARE);

    Surface image("../../../Images/Worms/wblink1.png");
    image.SetColorKey(true, SDL_MapRGB(image.Get()->format, 128,128,192));//los numeros magicos son
el rgb del fondo Texture sprites(renderer, image);

    // Enable alpha blending for the sprites
    //sprites.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Game state
    bool is_running = false; // whether the character is currently running
    int run_phase = -1;      // run animation phase
    float position = 0.0;    // player position

    unsigned int prev_ticks = SDL_GetTicks();
    // Main loop
    while (1) {
        unsigned int frame_ticks = SDL_GetTicks();
        unsigned int frame_delta = frame_ticks - prev_ticks;
        prev_ticks = frame_ticks;


        if (is_running) {
            position += frame_delta * 0.2;
            run_phase = (frame_ticks / 100) % 6;
        } else {
            run_phase = 0;
        }
        if (position > renderer.GetOutputWidth())
            position = -50;

        int vcenter = renderer.GetOutputHeight() / 2;

        renderer.Clear();

        int src_x = 0, src_y = 0;
        if (is_running) {
            src_x = 0;
            src_y = 60 * run_phase;
        }

        renderer.Copy(
                sprites,
                Rect(src_x, src_y, 50, 50),
                Rect((int)position, vcenter - 50, 50, 50)
            );

        renderer.Present();
        SDL_Delay(1);
    }



*/
