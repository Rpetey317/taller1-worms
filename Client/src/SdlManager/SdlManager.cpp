
#include "SdlManager.h"
#define FPS 30

void SdlManager::cheat_set_life_of_all_worms_to(int new_health) {
    for (auto& worm: worms) {
        worm.second->set_health(new_health);
    }
}

SdlManager::SdlManager(Queue<std::shared_ptr<Action>>& outgoing, Queue<std::shared_ptr<Event>>& ingoing, int id_of_player):
        outgoing(outgoing), ingoing(ingoing) {
    // Initialize SDL library
    // SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    this->id_of_player = id_of_player;
    this->id_of_player_turn = 1;
    id_worm_turn = 1;
    is_moving_camera = false;
    is_projectile_flying = false;
    is_animation_playing = false;
    // Initialize SDL_ttf library
    SDLTTF ttf;
}

bool SdlManager::event_handler() {
//VAMOS A ELEGIR ARMA CON NUMEROS 0 AL 9, YA QUE HAY 10 ARMAS :)
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            //worms[id_worm_turn]->destroy();
            return false;
        } else if (event.type == SDL_KEYDOWN) {
            if (id_of_player_turn != id_of_player || worms[id_worm_turn]->is_animation_playing)
                return true;

            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: {
                    //worms[id_worm_turn]->destroy();
                    //commands.push(0);
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
                    //ACA SETEO GUSANO EN "CARGANDO ARMA", Y A CADA TICK LE SUMO UNO EL PODER
                    worms[id_worm_turn]->play_sound("CHARGE");
                    worms[id_worm_turn]->is_charging = true;
                }
                break;
                
            }

        } else if (event.type == SDL_KEYUP) {
            if (id_of_player_turn != id_of_player || worms[id_worm_turn]->is_animation_playing)
                return true;
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT: {
                    worms[id_of_player]->change_state("STILL");
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
                //ESTA EN WIP ESTAS
                case SDLK_0:{ //BAZOOKA
                    worms[id_worm_turn]->change_state("BAZOOKA");
                    //worms[0]->worm_state = 3;
                    //PUSH DEL NUEVO ESTADO, NOMAS HAY QUE HACER UN BROADCAST AL RESTO DE GUSANOS PARA QUE ACTUALICEN
                    break;
                }
                case SDLK_1:{//MORTERO
                    worms[id_worm_turn]->change_state("MORTAR");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_2:{//GRANDA ROJA
                    worms[id_worm_turn]->change_state("RED_GRENADE");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_3:{//GRANADA VERDE
                    worms[id_worm_turn]->change_state("GREEN_GRENADE");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_4:{//BANANA
                    worms[id_worm_turn]->change_state("BANANA");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_5:{//GRANADA SANTA

                    worms[id_worm_turn]->change_state("HOLY_GRENADE");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_6:{//ATAQUE AEREO
                    worms[id_worm_turn]->change_state("AIR_STRIKE");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_7:{//DINAMITA
                    worms[id_worm_turn]->change_state("DYNAMITE");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_8:{//BATE DE BEISBOL
                    worms[id_worm_turn]->change_state("BEISBOLL");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_9:{//TELETRANSPORTACION
                    worms[id_worm_turn]->change_state("TELEPORT");
                    //worms[0]->worm_state = 3;
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
                    if (!worms[id_worm_turn]->has_ammo())
                        break;
                    worms[id_worm_turn]->reduce_ammo();
                    worms[id_worm_turn]->play_animation();
                    worms[id_worm_turn]->play_sound("THROWING");
                    outgoing.push(std::make_shared<Shoot>(worms[id_worm_turn]->projectile_id(), worms[id_worm_turn]->attack_power, worms[id_worm_turn]->angle));
                    worms[id_worm_turn]->is_charging = false;
                    worms[id_worm_turn]->attack_power = 0; //en vez de worms[0], deberiamos hacer worms[jugador_en_turno], osea voy a necesitar 2 variables mas
                    // uno es la variable del id jugador de este cliente, otro la variable del id jugador en turno :)
                    //push de que disparo algo
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
    // LAS POSICIONES DE TODOS LOS GUSANOS, EL ID DE TODOS LOS GUSANOS, Y EL ESTADO EN EL QUE ESTAN LOS GUSANOS
    // ESTADOS -> MOVIENDOSE, HACIENDO NADA, CAYENDO, LLEVANDO UNA DE 10 ARMAS

    //si se conecta un gusano nuevo, podria crear el worm y le pateo los managers, asi que ellos tienen el renderer :)
    renderer.Clear();
    map.draw_map();
    
    if (there_is_element) {
        //std::map<int, Vect2D> positions = event->get_worm_positions();
        std::map<int, Worm> server_worms = event->get_worms();
        for (auto& worm : worms) {
            if (!server_worms.empty()) {
                //el id de gusano =/= id de jugador controla al gusano
                worm.second->render_new(server_worms[worm.second->worm_id].position, server_worms[worm.second->worm_id].state);//deberia obtener el estado aca y se lo paso
            } else {
                worm.second->render_same();
            }
            worm.second->next_animation();
            worm.second->apply();
        }
        
        if (event->get_type_proyectile() != "NULL") {
            last_projectile_used = event->get_type_proyectile();
            is_projectile_flying = true;
            projectiles[last_projectile_used]->render(event->get_proyectile_position().x, event->get_proyectile_position().y, event->get_proyectile_angle());
        }
        if (event->proyectile_got_exploded()) {
            is_animation_playing = true;
        }
    
        if (event->get_player_turn() != -1) {
            id_worm_turn = event->get_player_turn();
            std::cout << "ID DE GUSANITO:" << id_worm_turn << std::endl;
            id_of_player_turn = worms[id_worm_turn]->player_id;
        }
        
        //std::cout << "WORM ID: " <<id_worm_turn << std::endl;
        //id_of_player_turn = worms[id_worm_turn]->player_id;


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

    renderer.Present();
}

void SdlManager::init_projectiles(SdlProjectilesTextureManager& projectiles_texture_manager, SdlCamera& camera) {
    projectiles["BAZOOKA"] = new SdlBazookaProjectile(projectiles_texture_manager, camera);
    projectiles["DYNAMITE"] = new SdlDynamiteProjectile(projectiles_texture_manager, camera);
    projectiles["HOLY_GRENADE"] = new SdlHolyGrenadeProjectile(projectiles_texture_manager, camera);
    projectiles["RED_GRENADE"] = new SdlRedGrenadeProjectile(projectiles_texture_manager, camera);
    projectiles["GREEN_GRENADE"] = new SdlGreenGrenadeProjectile(projectiles_texture_manager, camera);
    projectiles["MORTAR"] = new SdlMortarProjectile(projectiles_texture_manager, camera);
    projectiles["AIR_STRIKE"] = new SdlAirStrikeProjectile(projectiles_texture_manager, camera);
    projectiles["BANANA"] = new SdlBananaProjectile(projectiles_texture_manager, camera);
}

void SdlManager::run(std::string background_type, std::string selected_map) {
    //QUIZA LA IDEA ES QUE TENGA ACA UN POP PARA RECIBIR ESTE BACKGROUND_TYPE Y SELECTED_MAP???
    //COMO HACEMOS TEMA ANIMACIONES ENTRE MUCHOS PLAYERS???
    //TENGO UNA IDEA, ADEMAS DE RECIBIR POSICIONES GUSANOS, RECIBO SUS ID Y QUE ACCION REALIAZARON
    //SI ACCION ANTERIOR == LA QUE RECIBO -> EJECUTA PROX ANIMACION. SI ACCION ANTERIOR =/= LA QUE RECIBO, CAMBIO A ESA NUEVA ANIMACION :)
    //EL ID DEL PLAYER QUIZA LO RECIBO POR ACA O POR UNA QUEUE?

    const uint32_t frame_delay = 1000 / FPS;
    bool is_running = true;
    Window window("Worms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                  SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_SOFTWARE);
    camera.set_window(&window);
    
    SdlTexturesManager textures_manager(renderer, window, background_type);
    CommonMapParser parser;
    SdlMap map(camera, parser.get_map(selected_map), textures_manager);
    SdlSoundManager sound_manager;
    SdlWormTextureManager worm_texture_manager(renderer);
    SdlProjectilesTextureManager projectiles_texture_manager(renderer);
    init_projectiles(projectiles_texture_manager, camera);
    //aca creo los gusanos, pero deberia recibir como son los equipos y sus id
    std::vector<Tile> worms_positions = map.get_worms_positions();
    int i = 1;
    for (auto worm : worms_positions) {//me deberian pasar tambien la vida de los gusanitos
        worms[i] = new SdlWorm(camera, renderer, worm_texture_manager, sound_manager, worm.pos_x, worm.pos_y, i, i%3, 100);//hago este %2 para probar distintos id de jugadores
        i++;
    }

    while (is_running) {
        uint32_t frame_start;
        uint32_t frame_time;
        frame_start = SDL_GetTicks();
        is_running = main_loop(renderer, map, sound_manager, worm_texture_manager);
        // sleep(1); conexion super lagueada
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time)
            SDL_Delay(frame_delay - frame_time);
    }
}
