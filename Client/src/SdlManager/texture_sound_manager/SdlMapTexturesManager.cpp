#include "SdlMapTexturesManager.h"
#include <stdlib.h>
void SdlTexturesManager::draw_background() {
    SDL_Rect src,dest;
    src.x = src.y = dest.x = dest.y = 0;
    src.w = dest.w = window.GetWidth();
    src.h = dest.h = window.GetHeight();
    renderer.Copy(background, src,dest);
}

SdlTexturesManager::SdlTexturesManager(Renderer& renderer, Window& window, std::string background_type) :
 renderer(renderer), window(window),small_bridge(renderer, "../Images/TerrainSprites/bridge.png"), large_bridge(renderer, "../Images/TerrainSprites/large-bridge.png"), background(renderer, background_type) {
    
    Surface image_static("../Images/Worms/wblink1.png");
    image_static.SetColorKey(true, SDL_MapRGB(image_static.Get()->format, 128, 128,
                                       192));  
    worm = new Texture(renderer, image_static);

    Surface image_water_1("../Images/blue01.bmp");
    image_water_1.SetColorKey(true, SDL_MapRGB(image_water_1.Get()->format, 0, 0,
                                       0));  
    water1 = new Texture(renderer, image_water_1);

    Surface image_water_2("../Images/blue02.bmp");
    image_water_2.SetColorKey(true, SDL_MapRGB(image_water_2.Get()->format, 0, 0,
                                       0));  
    water2 = new Texture(renderer, image_water_2);

    Surface image_water_3("../Images/blue03.bmp");
    image_water_3.SetColorKey(true, SDL_MapRGB(image_water_3.Get()->format, 0, 0,
                                       0));  
    water3 = new Texture(renderer, image_water_3);

    src.x = src.y = 0;
    src.h = dest.h = 19;
    
}

void SdlTexturesManager::update_background(std::string background_type) {
    background = Texture(renderer, background_type);
}

void SdlTexturesManager::draw_editor(Tile& tile, int camera_x, int camera_y) {
    switch (tile.type) {
        case '0':
            src.w = dest.w = 64;
            src.h = dest.h = 19;
            dest.x = tile.pos_x - camera_x;
            dest.y = tile.pos_y - camera_y;
            renderer.Copy(small_bridge, src, dest, tile.angle, NullOpt, 0);
            break;
        case '1':
            src.w = dest.w = 128;
            src.h = dest.h = 19;
            dest.x = tile.pos_x - camera_x;
            dest.y = tile.pos_y - camera_y; 
            renderer.Copy(large_bridge, src, dest, tile.angle, NullOpt, 0);
            break;
        case '2':
            src.w = dest.w = 50;
            src.h = dest.h = 50;
            dest.x = tile.pos_x - camera_x;
            dest.y = tile.pos_y - camera_y;
            renderer.Copy(*worm, src, dest, 0, NullOpt, 0);
        default:
            break;
}
}

void SdlTexturesManager::draw_water(int camera_x, int camera_y) {
    
    src.w  = 128;
    dest.w = 128;
    src.h = 24;
    dest.h = 24 * 6;
    dest.x = 0;
    dest.y = MAP_HEIGHT - camera_y;
    for (int i = 0; i < MAP_WIDTH; i+= 128) {
        dest.x = i;
        if (i%3 == 0) {
            renderer.Copy(*water1, src, dest, 0, NullOpt, 0);
        } else if (i%3 == 1) {
            renderer.Copy(*water2, src, dest, 0, NullOpt, 0);
        } else {
            renderer.Copy(*water3, src, dest, 0, NullOpt, 0);
        }
        
    }
    
}

void SdlTexturesManager::draw(Tile& tile, int camera_x, int camera_y) {
    switch (tile.type) {
        case '0':
            src.w = dest.w = 64;
            src.h = dest.h = 19;
            dest.x = tile.pos_x - camera_x;
            dest.y = tile.pos_y - camera_y;
            renderer.Copy(small_bridge, src, dest, tile.angle, NullOpt, 0);
            break;
        case '1':
            src.w = dest.w = 128;
            src.h = dest.h = 19;
            dest.x = tile.pos_x - camera_x;
            dest.y = tile.pos_y - camera_y; 
            renderer.Copy(large_bridge, src, dest, tile.angle, NullOpt, 0);
            break;
        default:
            break;
    }
    
}

