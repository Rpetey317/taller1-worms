#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

#include <unistd.h>

#include "SdlManager.h"
#define FPS 15


using namespace SDL2pp;  // NOLINT

SdlMap::SdlMap(Renderer& renderer, Surface& image_floor1, Surface& image_floor2,
               Surface& image_floor3, Surface& image_water, Surface& image_background):
        floor1(renderer, image_floor1),
        floor2(renderer, image_floor2),
        floor3(renderer, image_floor3),
        background(renderer, image_background),
        water(renderer, image_water),
        renderer(renderer) {
    src.x = src.y = 0;
    src.w = dest.w = 64;
    src.h = dest.h = 19;
    dest.x = dest.y = 0;
    map[0][0] = 0;
}

void SdlMap::draw_map() {
    int type;
    for (int row = 0; row < 10; row++) {
        for (int column = 0; column < 10; column++) {
            type = map[row][column];

            dest.x = column * 64;
            dest.y = row * 19;

            switch (type) {
                case 0:

                    renderer.Copy(floor1, src, dest);
                    // renderer.Present();
                    break;
                case 1:
                    renderer.Copy(floor2, src, dest);
                    // renderer.Present();
                    break;
                case 2:
                    renderer.Copy(floor3, src, dest);
                    // renderer.Present();
                    break;
                case 3:
                    renderer.Copy(background, src, dest);
                    // renderer.Present();
                    break;
                default:
                    break;
            }
        }
    }
}
void SdlMap::load_map(int arr[10][10]) {
    for (int row = 0; row < 10; row++) {
        for (int column = 0; column < 10; column++) {
            map[row][column] = arr[row][column];
        }
    }
}

SdlWorm::SdlWorm(Texture& sprite): sprite(sprite), flip(SDL_FLIP_NONE) {
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

bool SdlManager::event_handler(SdlWorm& worm) {

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
                    worm.flip = SDL_FLIP_HORIZONTAL;
                    commands.push(1);
                    break;
                }
                case SDLK_LEFT: {
                    worm.flip = SDL_FLIP_NONE;
                    commands.push(2);
                    break;
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

bool SdlManager::main_loop(Renderer& renderer, SdlWorm& worm, SdlMap& map) {

    bool keep_playing = event_handler(worm);  // si me tiro un escape el player, keep_playing sera
                                              // false, para el resto siempre true
    // esto por si quiero cerrar de una forma un poco mas "linda"
    update_screen(renderer, worm, map);

    return keep_playing;
}

void SdlManager::run() {
    const int frame_delay = 1000 / FPS;
    bool is_running = true;
    Window window("PoC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                  SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_SOFTWARE);

    Surface image_floor1("../../../Images/Terrain/Construction/bridge.png");
    image_floor1.SetColorKey(true, 0);
    Surface image_floor2("../../../Images/Terrain/Construction/bridge-l.png");
    image_floor2.SetColorKey(true, 0);
    Surface image_floor3("../../../Images/Terrain/Construction/bridge-r.png");
    image_floor3.SetColorKey(true, 0);
    Surface image_water("../../../Images/Worms/wblink1.png");
    Surface image_background("../../../Images/Terrain/Hospital/soil.png");
    SdlMap map(renderer, image_floor1, image_floor2, image_floor3, image_water, image_background);
    int sarasa[10][10] = {
            {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
            {3, 3, 3, 3, 3, 0, 0, 3, 3, 3}, {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
            {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
            {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    };
    map.load_map(sarasa);
    Surface image("../../../Images/Worms/wblink1.png");

    image.SetColorKey(true, SDL_MapRGB(image.Get()->format, 128, 128,
                                       192));  // los numeros magicos son el rgb del fondo Texture

    Texture sprites(renderer, image);
    SdlWorm worm(sprites);
    worm.x_pos = 50;
    worm.y_pos = 50;
    worm.animation_phase = 0;

    while (is_running) {
        uint32_t frame_start;
        uint32_t frame_time;
        frame_start = SDL_GetTicks();
        is_running = main_loop(renderer, worm, map);
        // sleep(1); conexion super lagueada
        frame_time = SDL_GetTicks() - frame_start;

        if (frame_delay > frame_time)
            SDL_Delay(frame_delay - frame_time);
    }
}

void SdlManager::update_screen(Renderer& renderer, SdlWorm& worm, SdlMap& map) {
    std::vector<float> val;
    positions.try_pop(val);
    int src_x = 0, src_y = 0;

    if (!val.empty()) {
        renderer.Clear();
        src_x = 0;
        src_y = 60;
        Point center;
        // no se porque me pide center :(
        renderer.Copy(worm.sprite, Rect(src_x, src_y, 50, 50),
                      Rect((int)val[0], (int)val[1], 50, 50), 0, center, worm.flip);

    } else {
        renderer.Clear();

        map.draw_map();

        src_x = 0;
        src_y = 60 * worm.animation_phase;
        Point center;
        renderer.Copy(worm.sprite, Rect(src_x, src_y, 50, 50), Rect(worm.x_pos, worm.y_pos, 50, 50),
                      0, worm.flip);  // VERSION MODIFICADA DE COPY
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
