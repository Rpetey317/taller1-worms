#include "SdlWormTextureManager.h"

void SdlWormTextureManager::render(SdlWormState *worm_state, int animation_phase, int x_pos, int y_pos, SDL_RendererFlip flip) {
    Rect dest(x_pos, y_pos, 50, 50);
    worm_state->render(renderer, texture_map, dest, flip, animation_phase); 
}
// los numeros magicos son el rgb del fondo Texture
SdlWormTextureManager::SdlWormTextureManager(Renderer &renderer) : renderer(renderer) {


    //STATIC IMAGES
    Surface image_static("../Images/Worms/wblink1.png");
    image_static.SetColorKey(true, SDL_MapRGB(image_static.Get()->format, 128, 128,
                                       192));  
    texture_map["STILL"] = new Texture(renderer, image_static);
    Surface image_walk("../Images/Worms/wwalk.png");
    image_walk.SetColorKey(true, SDL_MapRGB(image_walk.Get()->format, 128, 128,
                                       192));  
    texture_map["WALK"] = new Texture(renderer, image_walk);
    Surface image_air_strike("../Images/Worms/wairtlku.png");
    image_air_strike.SetColorKey(true, SDL_MapRGB(image_air_strike.Get()->format, 128, 128,
                                       192));  
    texture_map["AIR_STRIKE"] = new Texture(renderer, image_air_strike);
    Surface image_bazooka("../Images/Worms/wbazu.png");//LA QUE TIENE ANGULOS
    image_bazooka.SetColorKey(true, SDL_MapRGB(image_bazooka.Get()->format, 128, 128,
                                       192));  
    texture_map["BAZOOKA"] = new Texture(renderer, image_bazooka);
    Surface image_beisboll("../Images/Worms/wbsbaimu.png");
    image_beisboll.SetColorKey(true, SDL_MapRGB(image_beisboll.Get()->format, 192, 192,
                                       128));  
    texture_map["BEISBOLL"] = new Texture(renderer, image_beisboll);
    Surface image_red_grenade("../Images/Worms/wthrcls.png");
    image_red_grenade.SetColorKey(true, SDL_MapRGB(image_red_grenade.Get()->format, 128, 128,
                                       192));  
    texture_map["RED_GRENADE"] = new Texture(renderer, image_red_grenade);
    Surface image_dynamite("../Images/Worms/wdynbaku.png");
    image_dynamite.SetColorKey(true, SDL_MapRGB(image_dynamite.Get()->format, 128, 128,
                                       192));  
    texture_map["DYNAMITE"] = new Texture(renderer, image_dynamite);
    Surface image_falling("../Images/Worms/wfall.png");
    image_falling.SetColorKey(true, SDL_MapRGB(image_falling.Get()->format, 128, 128,
                                       192));  
    texture_map["FALLING"] = new Texture(renderer, image_falling);
    Surface image_green_grenade("../Images/Worms/wthrgrn.png");
    image_green_grenade.SetColorKey(true, SDL_MapRGB(image_green_grenade.Get()->format, 128, 128,
                                       192));  
    texture_map["GREEN_GRENADE"] = new Texture(renderer, image_green_grenade);
    Surface image_holy_grenade("../Images/Worms/wthrhgr.png"); 
    image_holy_grenade.SetColorKey(true, SDL_MapRGB(image_holy_grenade.Get()->format, 128, 128,
                                       192));  
    texture_map["HOLY_GRENADE"] = new Texture(renderer, image_holy_grenade);
    Surface image_mortar("../Images/Worms/wbazu.png");//TIENE ANGULOS, IGUAL QUE BAZOOKA
    image_mortar.SetColorKey(true, SDL_MapRGB(image_mortar.Get()->format, 128, 128,
                                       192));  
    texture_map["MORTAR"] = new Texture(renderer, image_mortar);
    Surface image_teleport("../Images/Worms/wtelbaku.png");//ANIMACIONES 0 A 3
    image_teleport.SetColorKey(true, SDL_MapRGB(image_teleport.Get()->format, 192, 192,
                                       128));  
    texture_map["TELEPORT"] = new Texture(renderer, image_teleport);

    Surface image_banana("../Images/Worms/wthrban.png");
    image_banana.SetColorKey(true, SDL_MapRGB(image_banana.Get()->format, 128, 128,
                                       192));  //TIENE ANGULOS
    texture_map["BANANA"] = new Texture(renderer, image_banana);


    //ATTACKING ANIMATION


    Surface image_teleporting("../Images/Worms/wteldsv.png");
    image_teleporting.SetColorKey(true, SDL_MapRGB(image_teleporting.Get()->format, 192, 192,
                                       128));  
    texture_map["TELEPORTING"] = new Texture(renderer, image_teleporting);//LA QUE DESAPARECE UN POQUITO ANTES DE TELETRANSPORTARSE, ESTA TODO UN TEMA
    

    Surface image_beisboll_attack("../Images/Worms/wbsbbk2.png");
    image_beisboll_attack.SetColorKey(true, SDL_MapRGB(image_beisboll_attack.Get()->format, 192, 192,
                                       128));  
    texture_map["BEISBOLL_ATTACK"] = new Texture(renderer, image_beisboll_attack);

    // CHOOSING WEAPON ANIMATION

    Surface image_choosing_banana("../Images/Worms/wbanlnk.png");
    image_choosing_banana.SetColorKey(true, SDL_MapRGB(image_choosing_banana.Get()->format, 128, 128,
                                       192));  
    texture_map["CHOOSING_BANANA"] = new Texture(renderer, image_choosing_banana);    

    Surface image_choosing_bazooka("../Images/Worms/wbazlnk.png");
    image_choosing_bazooka.SetColorKey(true, SDL_MapRGB(image_choosing_bazooka.Get()->format, 128, 128,
                                       192));  
    texture_map["CHOOSING_BAZOOKA"] = new Texture(renderer, image_choosing_bazooka);   //QUE ES == A MORTERO

    Surface image_choosing_beisboll("../Images/Worms/wbsblnk.png");
    image_choosing_beisboll.SetColorKey(true, SDL_MapRGB(image_choosing_beisboll.Get()->format, 192, 192,
                                       128));  
    texture_map["CHOOSING_BEISBOLL"] = new Texture(renderer, image_choosing_beisboll); 

    Surface image_choosing_red_grenade("../Images/Worms/wclslnk.png");
    image_choosing_red_grenade.SetColorKey(true, SDL_MapRGB(image_choosing_red_grenade.Get()->format, 128, 128,
                                       192));  
    texture_map["CHOOSING_RED_GRENADE"] = new Texture(renderer, image_choosing_red_grenade);  

    Surface image_choosing_green_grenade("../Images/Worms/wgrnlnk.png");
    image_choosing_green_grenade.SetColorKey(true, SDL_MapRGB(image_choosing_green_grenade.Get()->format, 128, 128,
                                       192));  
    texture_map["CHOOSING_GREEN_GRENADE"] = new Texture(renderer, image_choosing_green_grenade);  

    Surface image_choosing_holy_grenade("../Images/Worms/whgrlnk.png");
    image_choosing_holy_grenade.SetColorKey(true, SDL_MapRGB(image_choosing_holy_grenade.Get()->format, 128, 128,
                                       192));  
    texture_map["CHOOSING_HOLY_GRENADE"] = new Texture(renderer, image_choosing_holy_grenade);  


    //other animations

    Surface image_die("../Images/Worms/wdie.png");
    image_die.SetColorKey(true, SDL_MapRGB(image_die.Get()->format, 128, 128,
                                       192));  
    texture_map["DIE"] = new Texture(renderer, image_die);  

    Surface image_fall("../Images/Worms/wfall.png");
    image_fall.SetColorKey(true, SDL_MapRGB(image_fall.Get()->format, 128, 128,
                                       192));  
    texture_map["FALL"] = new Texture(renderer, image_fall);  

}