
#include "SdlManager.h"
#define FPS 15
SdlManager::SdlManager(Queue<Action*>& outgoing, Queue<Event*>& ingoing, int id_of_player):
        outgoing(outgoing), ingoing(ingoing) {
    // Initialize SDL library
    // SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    this->id_of_player = id_of_player;
    this->id_of_player_turn = 0;
    // Initialize SDL_ttf library
    SDLTTF ttf;
}

bool SdlManager::event_handler() {
//VAMOS A ELEGIR ARMA CON NUMEROS 0 AL 9, YA QUE HAY 10 ARMAS :)
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            worms[id_of_player]->destroy();
            return false;
        } else if (event.type == SDL_KEYDOWN) {
            if (id_of_player_turn != id_of_player)
                return true;

            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: {
                    worms[id_of_player]->destroy();
                    //commands.push(0);
                    return false;
                }
                case SDLK_RIGHT: {
                    worms[id_of_player]->change_state("WALK");
                    worms[id_of_player]->flip = SDL_FLIP_HORIZONTAL;
                    outgoing.push(new Move(true));
                    break;
                }
                case SDLK_LEFT: {
                    worms[id_of_player]->change_state("WALK");
                    worms[id_of_player]->flip = SDL_FLIP_NONE;
                    outgoing.push(new Move(false));
                    break;
                }
                case SDLK_UP: {
                    if (!worms[id_of_player]->is_in_gun_state())
                        break;
                    worms[id_of_player]->change_angle(2);
                    break;
                }
                case SDLK_DOWN: {
                    if (!worms[id_of_player]->is_in_gun_state())
                        break;
                    worms[id_of_player]->change_angle(-2);
                    break;
                }
                break;
                
            }

        } else if (event.type == SDL_KEYUP) {
            if (id_of_player_turn != id_of_player)
                return true;
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT: {
                    worms[id_of_player]->change_state("STILL");
                    outgoing.push(new NullAction());
                    break;
                }
                case SDLK_LEFT: {
                    worms[id_of_player]->change_state("STILL");
                    //EL CAMBIO DE ESTADOS POSIBLEMENTE LO TENGA QUE CAMBIAR A CUANDO RECIBA DE LA QUEUE
                    // YA QUE AHI HARIA UN FOR CAMBIANDOLE EL ESTADO A TODOS LOS BICHOS
                    outgoing.push(new NullAction());
                    break;
                }
                //ESTA EN WIP ESTAS
                case SDLK_0:{ //BAZOOKA
                    worms[id_of_player]->change_state("BAZOOKA");
                    //worms[0]->worm_state = 3;
                    //PUSH DEL NUEVO ESTADO, NOMAS HAY QUE HACER UN BROADCAST AL RESTO DE GUSANOS PARA QUE ACTUALICEN
                    break;
                }
                case SDLK_1:{//MORTERO
                    worms[id_of_player]->change_state("MORTAR");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_2:{//GRANDA ROJA
                    worms[id_of_player]->change_state("RED_GRENADE");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_3:{//GRANADA VERDE
                    worms[id_of_player]->change_state("GREEN_GRENADE");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_4:{//BANANA
                    worms[id_of_player]->change_state("BANANA");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_5:{//GRANADA SANTA

                    worms[id_of_player]->change_state("HOLY_GRENADE");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_6:{//ATAQUE AEREO
                    worms[id_of_player]->change_state("AIR_STRIKE");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_7:{//DINAMITA
                    worms[id_of_player]->change_state("DYNAMITE");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_8:{//BATE DE BEISBOL
                    worms[id_of_player]->change_state("BEISBOLL");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_9:{//TELETRANSPORTACION
                    worms[id_of_player]->change_state("TELEPORT");
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_RETURN: { //SALTO HACIA DELANTE
                    outgoing.push(new Jump(true));
                    break;
                }
                case SDLK_BACKSPACE: {  //SALTO HACIA ATRAS
                    outgoing.push(new Jump(false));
                    break;
                }
                default: {

                    break;
                }

            }
        } else if(event.type == SDL_MOUSEBUTTONDOWN) {
            if (id_of_player_turn != id_of_player)
                return true;
            switch(event.button.button) {
                case SDL_BUTTON_LEFT : {
                    if (!worms[id_of_player]->is_in_gun_state())
                        break;
                    if (!worms[id_of_player]->has_ammo())
                        break;
                    //ACA SETEO GUSANO EN "CARGANDO ARMA", Y A CADA TICK LE SUMO UNO EL PODER
                    worms[id_of_player]->play_sound("CHARGE");
                    worms[id_of_player]->is_charging = true;
                    break;
                } 
                default: {
                    break;
                }
            }

        } else if (event.type == SDL_MOUSEBUTTONUP) {
            if (id_of_player_turn != id_of_player)
                return true;
            switch(event.button.button) {
                case SDL_BUTTON_LEFT : {
                    if (!worms[id_of_player]->is_in_gun_state())
                        break;
                    if (!worms[id_of_player]->has_ammo())
                        break;
                    worms[id_of_player]->reduce_ammo();
                    std::cout << "ATTACK_POWER: " << worms[id_of_player]->attack_power << std::endl;
                    worms[id_of_player]->play_sound("THROWING");
                    worms[id_of_player]->is_charging = false;
                    worms[id_of_player]->attack_power = 0; //en vez de worms[0], deberiamos hacer worms[jugador_en_turno], osea voy a necesitar 2 variables mas
                    // uno es la variable del id jugador de este cliente, otro la variable del id jugador en turno :)
                    //push de que disparo algo
                    break;
                }
                default: {
                    break;
                }
                
            }

        }
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
    Event *val;
    bool there_is_element = ingoing.try_pop(val);
    // LAS POSICIONES DE TODOS LOS GUSANOS, EL ID DE TODOS LOS GUSANOS, Y EL ESTADO EN EL QUE ESTAN LOS GUSANOS
    // ESTADOS -> MOVIENDOSE, HACIENDO NADA, CAYENDO, LLEVANDO UNA DE 10 ARMAS

    //si se conecta un gusano nuevo, podria crear el worm y le pateo los managers, asi que ellos tienen el renderer :)
    renderer.Clear();
    map.draw_map();
    
    if (there_is_element) {
        for (auto& worm : worms) {
            val->get_worm_positions()[1];
            worm.second->render_same();
            worm.second->next_animation();
            worm.second->apply();
        }
    } else {  //SI NO RECIBO NADA, SEGUI EJECUTANDO LA ANTERIOR ANIMACION Y QUEDATE EN EL MISMO LUGAR

        for (auto& worm : worms) {
            worm.second->render_same();
            worm.second->next_animation();
            worm.second->apply();
        }
    }

    id_of_player_turn = 0;//ESTO LO RECIBIRIA CON EL RESTO DE COSAS :)
    

    renderer.Present();
}

void SdlManager::run(std::string background_type, std::string selected_map) {
    //QUIZA LA IDEA ES QUE TENGA ACA UN POP PARA RECIBIR ESTE BACKGROUND_TYPE Y SELECTED_MAP???
    //COMO HACEMOS TEMA ANIMACIONES ENTRE MUCHOS PLAYERS???
    //TENGO UNA IDEA, ADEMAS DE RECIBIR POSICIONES GUSANOS, RECIBO SUS ID Y QUE ACCION REALIAZARON
    //SI ACCION ANTERIOR == LA QUE RECIBO -> EJECUTA PROX ANIMACION. SI ACCION ANTERIOR =/= LA QUE RECIBO, CAMBIO A ESA NUEVA ANIMACION :)
    //EL ID DEL PLAYER QUIZA LO RECIBO POR ACA O POR UNA QUEUE?

    const uint32_t frame_delay = 1000 / FPS;
    bool is_running = true;
    Window window("PoC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                  SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_SOFTWARE);
    
    SdlTexturesManager textures_manager(renderer, window, background_type);
    CommonMapParser parser;
    SdlMap map(parser.get_map(selected_map), textures_manager);
    SdlSoundManager sound_manager;
    SdlWormTextureManager worm_texture_manager(renderer);
    //LA CREACION DEL NUEVO GUSANO LA HARIA EN EL UPDATE_SCREEN, YA QUE ES DONDE HAGO EL POP
    // AHI RECIBIRIA EL MENSAJE DE CREAR NUEVO GUSANO :)
    worms[id_of_player] = new SdlWorm(worm_texture_manager, sound_manager);
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