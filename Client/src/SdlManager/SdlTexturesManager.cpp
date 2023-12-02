#include "SdlTexturesManager.h"

void SdlTexturesManager::draw_background() {
    SDL_Rect src,dest;
    src.x = src.y = dest.x = dest.y = 0;
    src.w = dest.w = window.GetWidth();
    src.h = dest.h = window.GetHeight();
    renderer.Copy(background, src,dest);
}

SdlTexturesManager::SdlTexturesManager(Renderer& renderer, Window& window, std::string background_type) :
 renderer(renderer), window(window),small_bridge(renderer, "../Images/TerrainSprites/bridge.png"), large_bridge(renderer, "../Images/TerrainSprites/large-bridge.png"), water(renderer, "../Images/Worms/wblink1.png"), background(renderer, background_type) {
    
    src.x = src.y = 0;
    src.h = dest.h = 19;
}

void SdlTexturesManager::draw(Tile& tile, int camera_x, int camera_y) {
    switch (tile.type) {
        case '0':
            src.w = dest.w = 64;
            dest.x = tile.pos_x - camera_x;
            dest.y = tile.pos_y - camera_y;
            renderer.Copy(small_bridge, src, dest, tile.angle, NullOpt, 0);
            break;
        case '1':
            src.w = dest.w = 128;
            dest.x = tile.pos_x - camera_x;
            dest.y = tile.pos_y - camera_y; 
            renderer.Copy(large_bridge, src, dest, tile.angle, NullOpt, 0);
            break;
        default:
            break;
    }
    
}

