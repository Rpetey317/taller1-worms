#include "SdlProjectilesTextureManager.h"




SdlProjectilesTextureManager::SdlProjectilesTextureManager(Renderer& renderer) : renderer(renderer) {
    Surface image_banana("../Images/Weapons/banana.png");
    image_banana.SetColorKey(true, SDL_MapRGB(image_banana.Get()->format, 128, 128,
                                       192));  
    texture_map["BANANA"] = new Texture(renderer, image_banana);

    Surface image_red_grenade("../Images/Weapons/cluster.png");
    image_red_grenade.SetColorKey(true, SDL_MapRGB(image_red_grenade.Get()->format, 128, 128,
                                       192));  
    texture_map["RED_GRENADE"] = new Texture(renderer, image_red_grenade);

    Surface image_red_grenade_shard("../Images/Weapons/clustlet.png");
    image_red_grenade_shard.SetColorKey(true, SDL_MapRGB(image_red_grenade_shard.Get()->format, 128, 128,
                                       192));  
    texture_map["RED_GRENADE_SHARD"] = new Texture(renderer, image_red_grenade_shard);

    Surface image_dynamite("../Images/Weapons/dynamite.png");
    image_dynamite.SetColorKey(true, SDL_MapRGB(image_dynamite.Get()->format, 128, 128,
                                       192));  
    texture_map["DYNAMITE"] = new Texture(renderer, image_dynamite);

    Surface image_green_grenade("../Images/Weapons/grenade.png");
    image_green_grenade.SetColorKey(true, SDL_MapRGB(image_green_grenade.Get()->format, 128, 128,
                                       192));  
    texture_map["GREEN_GRENADE"] = new Texture(renderer, image_green_grenade);

    Surface image_holy_grenade("../Images/Weapons/hgrenade.png");
    image_holy_grenade.SetColorKey(true, SDL_MapRGB(image_holy_grenade.Get()->format, 128, 128,
                                       192));  
    texture_map["HOLY_GRENADE"] = new Texture(renderer, image_holy_grenade);

    Surface image_bazooka("../Images/Weapons/missile.png");
    image_bazooka.SetColorKey(true, SDL_MapRGB(image_bazooka.Get()->format, 192, 192,
                                       128));  
    texture_map["BAZOOKA"] = new Texture(renderer, image_bazooka);

    Surface image_mortar("../Images/Weapons/mortar.png");
    image_mortar.SetColorKey(true, SDL_MapRGB(image_mortar.Get()->format, 192, 192,
                                       128));  
    texture_map["MORTAR"] = new Texture(renderer, image_mortar);

    Surface image_air_strike("../Images/Weapons/hmissil2.png");
    image_air_strike.SetColorKey(true, SDL_MapRGB(image_air_strike.Get()->format, 192, 192,
                                       128));  
    texture_map["AIR_STRIKE"] = new Texture(renderer, image_air_strike);

    Surface image_air_strike_plane("../Images/Weapons/airjetb.png");
    image_air_strike_plane.SetColorKey(true, SDL_MapRGB(image_air_strike_plane.Get()->format, 192, 192,
                                       128));  
    texture_map["AIR_STRIKE_PLANE"] = new Texture(renderer, image_air_strike_plane);



    Surface image_elipse("../Images/Effects/elipse25.png");
    image_elipse.SetColorKey(true, SDL_MapRGB(image_elipse.Get()->format, 32, 32,
                                       248));  
    texture_map["ELIPSE"] = new Texture(renderer, image_elipse);

    Surface image_expoot("../Images/Effects/expoot.png");
    image_expoot.SetColorKey(true, SDL_MapRGB(image_expoot.Get()->format, 128, 128,
                                       192));  
    texture_map["EXPOOT"] = new Texture(renderer, image_expoot);


    Surface image_petrol1("../Images/Effects/petrol1.png");
    image_petrol1.SetColorKey(true, SDL_MapRGB(image_petrol1.Get()->format, 128, 128,
                                       192));  
    texture_map["BOOM"] = new Texture(renderer, image_petrol1);

}

void SdlProjectilesTextureManager::render(std::string& projectile, int x_pos, int y_pos, int angle, int animation_phase) {
        renderer.Copy(*texture_map[projectile], Rect(0, 60 * animation_phase, 50, 50), Rect(x_pos, y_pos, 50, 50), angle, NullOpt, 0);
}

void SdlProjectilesTextureManager::render_explosion(int x_pos, int y_pos, int animation_phase) {
        renderer.Copy(*texture_map["ELIPSE"], Rect(0, 74 * animation_phase, 74, 74), Rect(x_pos, y_pos, 60, 60));
        renderer.Copy(*texture_map["EXPOOT"], Rect(0, 70 * animation_phase, 70, 70), Rect(x_pos, y_pos, 60, 60));
        renderer.Copy(*texture_map["BOOM"], Rect(0, 60 * animation_phase, 60, 60), Rect(x_pos, y_pos, 60, 60));
}
