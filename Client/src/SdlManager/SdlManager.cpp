
#include "SdlManager.h"
#define FPS 45
#define CONSTANT_WAIT 1000 / FPS
void SdlManager::cheat_set_life_of_all_worms_to(int new_health) {
    for (auto& worm: worms) {
        worm.second->set_health(new_health);
    }
}

SdlManager::SdlManager(Queue<std::shared_ptr<Action>>& outgoing, Queue<std::shared_ptr<Event>>& ingoing):
        outgoing(outgoing), ingoing(ingoing) {
    // Initialize SDL library
    // SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    this->id_of_player_turn = 1;
    id_worm_turn = 1;
    is_moving_camera = false;
    is_projectile_flying = false;
    is_animation_playing = false;
    timer_rect.set_color(0, 0, 255);
    timer_rect.set_height(10);
    timer_rect.set_width(0);
    // Initialize SDL_ttf library
    last_projectile_used = "NULL";
    SDLTTF ttf;
}

bool SdlManager::event_handler() {
        
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        } else if (event.type == SDL_KEYDOWN) {
            if (id_of_player_turn != worms[id_worm_turn]->player_id || worms[id_worm_turn]->is_animation_playing)
                return true;

            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: {
                    return false;
                }
                case SDLK_RIGHT: {
                    worms[id_worm_turn]->change_state("WALK");
                    worms[id_worm_turn]->flip = SDL_FLIP_HORIZONTAL;
                    outgoing.push(std::make_shared<Move>(true));
                    break;
                }
                case SDLK_LEFT: {
                    worms[id_worm_turn]->change_state("WALK");
                    worms[id_worm_turn]->flip = SDL_FLIP_NONE;
                    outgoing.push(std::make_shared<Move>(false));
                    break;
                }
                case SDLK_UP: {
                    if (!worms[id_worm_turn]->is_in_gun_state())
                        break;
                    worms[id_worm_turn]->change_angle(2);
                    break;
                }
                case SDLK_DOWN: {
                    if (!worms[id_worm_turn]->is_in_gun_state())
                        break;
                    worms[id_worm_turn]->change_angle(-2);
                    break;
                }
                case SDLK_F1: {    //recargar balas
                    worms[id_worm_turn]->recharge_ammo();
                    break;
                }
                case SDLK_F2: {    // setear vida en 100 a todos los gusanos
                    cheat_set_life_of_all_worms_to(100);
                    break;
                }
                case SDLK_F3: {    // setear vida en 1 a todos los gusanos
                    cheat_set_life_of_all_worms_to(1);
                    break;
                }
                case SDLK_SPACE: {
                    if (!worms[id_worm_turn]->is_in_gun_state())
                        break;
                    if (!worms[id_worm_turn]->has_ammo())
                        break;
                        
                    worms[id_worm_turn]->is_charging = true;
                }
                break;
                
            }

        } else if (event.type == SDL_KEYUP) {
            if (id_of_player_turn != worms[id_worm_turn]->player_id || worms[id_worm_turn]->is_animation_playing)
                return true;
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT: {
                    worms[id_worm_turn]->change_state("STILL");
                    outgoing.push(std::make_shared<NullAction>());
                    break;
                }
                case SDLK_LEFT: {
                    worms[id_worm_turn]->change_state("STILL");
                    //EL CAMBIO DE ESTADOS POSIBLEMENTE LO TENGA QUE CAMBIAR A CUANDO RECIBA DE LA QUEUE
                    // YA QUE AHI HARIA UN FOR CAMBIANDOLE EL ESTADO A TODOS LOS BICHOS
                    outgoing.push(std::make_shared<NullAction>());
                    break;
                }
                
                case SDLK_0:{ //BAZOOKA
                    worms[id_worm_turn]->change_state("BAZOOKA");
                    outgoing.push(std::make_shared<ChangeWeapon>(BAZOOKA));
                    break;
                }
                case SDLK_1:{//MORTERO
                    worms[id_worm_turn]->change_state("MORTAR");
                    outgoing.push(std::make_shared<ChangeWeapon>(MORTAR));
                    break;
                }
                case SDLK_2:{//GRANDA ROJA
                    worms[id_worm_turn]->change_state("RED_GRENADE");
                    outgoing.push(std::make_shared<ChangeWeapon>(RED_GRANADE));
                    break;
                }
                case SDLK_3:{//GRANADA VERDE
                    worms[id_worm_turn]->change_state("GREEN_GRENADE");
                    outgoing.push(std::make_shared<ChangeWeapon>(GREEN_GRANADE));
                    break;
                }
                case SDLK_4:{//BANANA
                    worms[id_worm_turn]->change_state("BANANA");
                    outgoing.push(std::make_shared<ChangeWeapon>(BANANA));
                    break;
                }
                case SDLK_5:{//GRANADA SANTA
                    worms[id_worm_turn]->change_state("HOLY_GRENADE");
                    outgoing.push(std::make_shared<ChangeWeapon>(HOLY_GRANADE));
                    break;
                }
                case SDLK_6:{//ATAQUE AEREO
                    worms[id_worm_turn]->change_state("AIR_STRIKE");
                    outgoing.push(std::make_shared<ChangeWeapon>(AIR_STRIKE));
                    break;
                }
                case SDLK_7:{//DINAMITA
                    worms[id_worm_turn]->change_state("DYNAMITE");
                    outgoing.push(std::make_shared<ChangeWeapon>(DYNAMITE));
                    break;
                }
                case SDLK_8:{//BATE DE BEISBOL
                    worms[id_worm_turn]->change_state("BEISBOLL");
                    outgoing.push(std::make_shared<ChangeWeapon>(BASEBALL_BAT));
                    break;
                }
                case SDLK_9:{//TELETRANSPORTACION
                    worms[id_worm_turn]->change_state("TELEPORT");
                    outgoing.push(std::make_shared<ChangeWeapon>(TELEPORT));
                    break;
                }
                case SDLK_RETURN: { //SALTO HACIA DELANTE
                    outgoing.push(std::make_shared<Jump>(true));
                    break;
                }
                case SDLK_BACKSPACE: {  //SALTO HACIA ATRAS
                    outgoing.push(std::make_shared<Jump>(false));
                    break;
                }
                case SDLK_SPACE: {
                    if (worms[id_worm_turn]->already_fired)
                        break;
                    if (!worms[id_worm_turn]->has_ammo())
                        break;
                    worms[id_worm_turn]->reduce_ammo();
                    worms[id_worm_turn]->play_animation();
                    worms[id_worm_turn]->play_sound();
                    outgoing.push(std::make_shared<Shoot>(worms[id_worm_turn]->projectile_id(), worms[id_worm_turn]->attack_power, worms[id_worm_turn]->angle));
                    worms[id_worm_turn]->is_charging = false;
                    worms[id_worm_turn]->already_fired = true;
                    worms[id_worm_turn]->attack_power = 0; 
                    break;
                }
                default: {

                    break;
                }

            }
        } else if(event.type == SDL_MOUSEBUTTONDOWN) {

            switch(event.button.button) {
                
                case SDL_BUTTON_LEFT : {
                    is_moving_camera = true;
                    break;
                }
                default: {
                    break;
                }
            }

        } else if (event.type == SDL_MOUSEBUTTONUP) {
            switch(event.button.button) {
                case SDL_BUTTON_LEFT : {
                    is_moving_camera = false;
                    break;
                }
                default: {
                    break;
                }
                
            }

        }

        
    }

    if (!is_moving_camera) {
        if (is_projectile_flying) {
            camera.focus_object(projectiles[last_projectile_used]->get_pos_x(), projectiles[last_projectile_used]->get_pos_y());
        } else {
            camera.focus_object(worms[id_worm_turn]->x_pos, worms[id_worm_turn]->y_pos);

        }
    } else {
        int x_pos;
        int y_pos;
        SDL_GetMouseState(&x_pos, &y_pos);
        camera.focus_object(x_pos - camera.get_width(), y_pos - camera.get_height());
    }

    return true;
}

bool SdlManager::main_loop(Renderer& renderer, SdlMap& map, SdlSoundManager& sound_manager, SdlWormTextureManager& worm_texture_manager) {

    bool keep_playing = event_handler();  // si me tiro un escape el player, keep_playing
                                                    // sera false, para el resto siempre true
    // esto por si quiero cerrar de una forma un poco mas "linda"
    update_screen(renderer, map, sound_manager, worm_texture_manager);

    return keep_playing;
}
void SdlManager::update_screen(Renderer& renderer, SdlMap& map, SdlSoundManager& sound_manager, SdlWormTextureManager& worm_texture_manager) {
    std::shared_ptr<Event> event;
    bool there_is_element = ingoing.try_pop(event);
    // LAS POSICIONES DE TODOS LOS GUSANOS, EL ID DE TODOS LOS GUSANOS, EL ESTADO EN EL QUE ESTAN LOS GUSANOS, Y LA VIDA

    renderer.Clear();
    map.draw_map();
    
    if (there_is_element) {
        std::map<int, Worm> server_worms = event->get_worms();
        for (auto& worm : worms) {

            if (!server_worms.empty()) {
                //el id de gusano =/= id de jugador controla al gusano
                worm.second->render_new(server_worms[worm.second->worm_id].position, server_worms[worm.second->worm_id].state, server_worms[worm.second->worm_id].health_points);//deberia obtener el estado aca y se lo paso
                
            } else {
                worm.second->render_same();
            }
            worm.second->next_animation();
            worm.second->apply();
        }

        std::list<WeaponDTO> weapons = event->get_weapons();
        if (!weapons.empty()) {
            for (auto weapon : weapons) {
                is_projectile_flying = true;
                switch (weapon.id)
                {
                case BAZOOKA:
                    last_projectile_used = "BAZOOKA";
                    break;
                case MORTAR:
                    last_projectile_used = "MORTAR";
                    break;
                case GREEN_GRANADE:
                    last_projectile_used = "GREEN_GRENADE";
                    break;
                case RED_GRANADE:
                    last_projectile_used = "RED_GRENADE";
                    break;
                case BANANA:
                    last_projectile_used = "BANANA";
                    break;
                case HOLY_GRANADE:
                    last_projectile_used = "HOLY_GRENADE";
                    break;
                case AIR_STRIKE:
                    last_projectile_used = "AIR_STRIKE";
                    break;
                case BASEBALL_BAT:
                    last_projectile_used = "BEISBOLL";
                    break;
                case DYNAMITE:
                    last_projectile_used = "DYNAMITE";
                    break;
                case TELEPORT:
                    last_projectile_used = "TELEPORT";
                    break;
                case EXPLOSION:
                    std::cout << "DALE BOCA" << std::endl;
                    last_projectile_used = last_projectile_used;
                    is_projectile_flying = false;
                    is_animation_playing = true;
                    projectiles[last_projectile_used]->play_sound();
                    break;
                default:
                    last_projectile_x = 0;
                    last_projectile_y = 0;
                    last_projectile_angle = 0;
                    is_projectile_flying = false;
                    last_projectile_used = "NULL";
                    break;
                    
                }

                last_projectile_x = weapon.position.x;
                last_projectile_y = weapon.position.y;
                last_projectile_angle = weapon.angle;

            }
        }
        if (last_projectile_used != "NULL")
            projectiles[last_projectile_used]->render(last_projectile_x, last_projectile_y, last_projectile_angle);   

        if (event->get_player_turn() > 0) {
            if (id_worm_turn != event->get_player_turn()) {
                worms[id_worm_turn]->angle = 0;
                worms[id_worm_turn]->is_charging = false;
                worms[id_worm_turn]->attack_power = 0;
            }
            id_worm_turn = event->get_player_turn();
            worms[id_worm_turn]->already_fired = false;
            timer = event->get_duration();
            if (timer <= 3) {
                timer_rect.set_color(255, 0, 0);
            } else {
                timer_rect.set_color(0, 0, 255);
            }
            timer_rect.set_width(timer * 2);
            timer_rect.set_position(10, camera.get_window_height() - 20);

        }


    } else {  //SI NO RECIBO NADA, SEGUI EJECUTANDO LA ANTERIOR ANIMACION Y QUEDATE EN EL MISMO LUGAR

        for (auto& worm : worms) {
            worm.second->render_same();
            worm.second->next_animation();
            worm.second->apply();
        }
    }

    if (is_animation_playing) {
        projectiles[last_projectile_used]->play_animation(&is_animation_playing);
        if (!is_animation_playing)
            is_projectile_flying = false;
    }
    timer_rect.render(renderer);
    renderer.Present();
}

void SdlManager::init_projectiles(SdlSoundManager& sound_manager, SdlProjectilesTextureManager& projectiles_texture_manager, SdlCamera& camera) {
    projectiles["BAZOOKA"] = new SdlBazookaProjectile(sound_manager, projectiles_texture_manager, camera);
    projectiles["DYNAMITE"] = new SdlDynamiteProjectile(sound_manager, projectiles_texture_manager, camera);
    projectiles["HOLY_GRENADE"] = new SdlHolyGrenadeProjectile(sound_manager, projectiles_texture_manager, camera);
    projectiles["RED_GRENADE"] = new SdlRedGrenadeProjectile(sound_manager, projectiles_texture_manager, camera);
    projectiles["GREEN_GRENADE"] = new SdlGreenGrenadeProjectile(sound_manager, projectiles_texture_manager, camera);
    projectiles["MORTAR"] = new SdlMortarProjectile(sound_manager, projectiles_texture_manager, camera);
    projectiles["AIR_STRIKE"] = new SdlAirStrikeProjectile(sound_manager, projectiles_texture_manager, camera);
    projectiles["BANANA"] = new SdlBananaProjectile(sound_manager, projectiles_texture_manager, camera);
}

void SdlManager::run(std::string selected_map) {
    //QUIZA LA IDEA ES QUE TENGA ACA UN POP PARA RECIBIR ESTE BACKGROUND_TYPE Y SELECTED_MAP???
    //COMO HACEMOS TEMA ANIMACIONES ENTRE MUCHOS PLAYERS???
    //TENGO UNA IDEA, ADEMAS DE RECIBIR POSICIONES GUSANOS, RECIBO SUS ID Y QUE ACCION REALIAZARON
    //SI ACCION ANTERIOR == LA QUE RECIBO -> EJECUTA PROX ANIMACION. SI ACCION ANTERIOR =/= LA QUE RECIBO, CAMBIO A ESA NUEVA ANIMACION :)
    //EL ID DEL PLAYER QUIZA LO RECIBO POR ACA O POR UNA QUEUE?

    bool is_running = true;
    Window window("Worms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                  SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_SOFTWARE);
    camera.set_window(&window);

    std::shared_ptr<Event> first_event;
    while(!ingoing.try_pop(first_event)) {
    }
    id_of_player_turn = first_event->get_id();
    while (!ingoing.try_pop(first_event)) {
    }
    std::map<int, Worm> worms_positions = first_event->get_worms();
    CommonMapParser parser;
    SdlTexturesManager textures_manager(renderer, window, parser.get_background(worms_positions[1].map_name));
    SdlMap map(camera, parser.get_map(worms_positions[1].map_name), textures_manager);
    SdlSoundManager sound_manager;
    SdlWormTextureManager worm_texture_manager(renderer);
    SdlProjectilesTextureManager projectiles_texture_manager(renderer);
    init_projectiles(sound_manager,  projectiles_texture_manager, camera);    
    int i = 1;
    for (auto worm : worms_positions) {
        worms[i] = new SdlWorm(camera, renderer, worm_texture_manager, sound_manager, worm.second.position.x, worm.second.position.y, i, worm.second.player_id, worm.second.health_points);
        i++;
    }
    int time_lost = 0;
	int timer_init; 
	int timer_finish;
    while (is_running) {
        timer_init = SDL_GetTicks(); 
        is_running = main_loop(renderer, map, sound_manager, worm_texture_manager);
        // sleep(1); conexion super lagueada
        timer_finish = SDL_GetTicks();
        int to_sleep = CONSTANT_WAIT - (timer_finish-timer_init) - time_lost;
		if (to_sleep < 0) {
			time_lost = 0;
		} else {
			SDL_Delay(to_sleep);
			time_lost = SDL_GetTicks() - (timer_finish + to_sleep);
		}
    }
}
