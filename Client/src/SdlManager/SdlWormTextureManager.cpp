#include "SdlWormTextureManager.h"

void SdlWormTextureManager::render(SdlWormState *worm_state, int animation_phase, int x_pos, int y_pos, SDL_RendererFlip flip) {
    Rect dest(x_pos, y_pos, 50, 50);
    worm_state->render(renderer, texture_map, dest, flip, animation_phase); 
}

SdlWormTextureManager::SdlWormTextureManager(Renderer &renderer) : renderer(renderer) {
    Surface image_static("../../../Images/Worms/wblink1.png");
    image_static.SetColorKey(true, SDL_MapRGB(image_static.Get()->format, 128, 128,
                                       192));  // los numeros magicos son el rgb del fondo Texture
    texture_map["STATIC"] = new Texture(renderer, image_static);
    Surface image_walk("../../../Images/Worms/wwalk.png");
    image_walk.SetColorKey(true, SDL_MapRGB(image_walk.Get()->format, 128, 128,
                                       192));  
    texture_map["WALK"] = new Texture(renderer, image_walk);


}