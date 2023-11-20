
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
                    delete worms[id_of_player]->worm_state;
                    worms[id_of_player]->worm_state = new SdlWormStateWalk();
                    worms[id_of_player]->flip = SDL_FLIP_HORIZONTAL;
                    worms[id_of_player]->angle = 0;
                    outgoing.push(new Move(true));
                    break;
                }
                case SDLK_LEFT: {
                    delete worms[id_of_player]->worm_state;
                    worms[id_of_player]->worm_state = new SdlWormStateWalk();
                    worms[id_of_player]->flip = SDL_FLIP_NONE;
                    worms[id_of_player]->angle = 0;
                    outgoing.push(new Move(false));
                    break;
                }
                case SDLK_UP: {
                    std::cout << "cambiando angulo..." << std::endl;
                    worms[id_of_player]->angle = worms[id_of_player]->angle + 1;
                    //buscar como mostrar el angulo en la pantalla de alguna forma
                    break;
                }
                case SDLK_DOWN: {
                    //verificar que este en algun modo arma
                    std::cout << "cambiando angulo..." << worms[id_of_player]->angle << std::endl;
                    worms[id_of_player]->angle = worms[id_of_player]->angle -1;
                    //verificar no se pase de +- 90 el angulo
                    break;
                }
                break;
                
            }

        } else if (event.type == SDL_KEYUP) {
            if (id_of_player_turn != id_of_player)
                return true;
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT: {
                    delete worms[id_of_player]->worm_state;
                    worms[id_of_player]->worm_state = new SdlWormStateStill();
                    worms[id_of_player]->animation_phase = 0;
                    outgoing.push(new NullAction());
                    break;
                }
                case SDLK_LEFT: {
                    //crear mensaje de gusano "change_state", donde le paso el nuevo state.
                    // en ese mensaje se libera la memoria, seteo el animation_phase y pongo el is_charging en lo que corresponda
                    delete worms[id_of_player]->worm_state;
                    worms[id_of_player]->worm_state = new SdlWormStateStill();
                    //EL CAMBIO DE ESTADOS POSIBLEMENTE LO TENGA QUE CAMBIAR A CUANDO RECIBA DE LA QUEUE
                    // YA QUE AHI HARIA UN FOR CAMBIANDOLE EL ESTADO A TODOS LOS BICHOS
                    worms[id_of_player]->animation_phase = 0;
                    outgoing.push(new NullAction());
                    break;
                }
                //ESTA EN WIP ESTAS
                case SDLK_0:{ //BAZOOKA

                    //worms[0]->worm_state = 3;

                    break;
                }
                case SDLK_1:{//MORTERO
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_2:{//GRANDA ROJA
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_3:{//GRANADA VERDE
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_4:{//BANANA
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_5:{//GRANADA SANTA
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_6:{//ATAQUE AEREO
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_7:{//DINAMITA
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_8:{//BATE DE BEISBOL
                    //worms[0]->worm_state = 3;
                    break;
                }
                case SDLK_9:{//TELETRANSPORTACION
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
                    //if (!worms[id_of_player].esta_en_modo_arma)
                    //    break;
                    //ACA SETEO GUSANO EN "CARGANDO ARMA", Y A CADA TICK LE SUMO UNO EL PODER
                    worms[id_of_player]->play_sound("CHARGE");
                    worms[id_of_player]->is_charging = true;
                    //delete worms[id_of_player]->worm_state; se va a mantener en el modo arma
                    //worms[id_of_player]->worm_state = new SdlWormStateStill();
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
                    //if (!worms[id_of_player].esta_en_modo_arma)
                    //    break;
                    std::cout << "ATTACK_POWER: " << worms[0]->attack_power << std::endl;
                    worms[id_of_player]->play_sound("THROWING");
                    delete worms[id_of_player]->worm_state;
                    worms[id_of_player]->worm_state = new SdlWormStateStill();
                    //commands.push(6);
                    worms[id_of_player]->is_charging = false;
                    worms[id_of_player]->attack_power = 0; //en vez de worms[0], deberiamos hacer worms[jugador_en_turno], osea voy a necesitar 2 variables mas
                    // uno es la variable del id jugador de este cliente, otro la variable del id jugador en turno :)
                    
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

bool SdlManager::main_loop(Renderer& renderer, SdlMap& map) {

    bool keep_playing = event_handler();  // si me tiro un escape el player, keep_playing
                                                    // sera false, para el resto siempre true
    // esto por si quiero cerrar de una forma un poco mas "linda"
    update_screen(renderer, map);

    return keep_playing;
}
void SdlManager::update_screen(Renderer& renderer, SdlMap& map) {
    Event *val;
    bool is_empty = ingoing.try_pop(val);
    // LAS POSICIONES DE TODOS LOS GUSANOS, EL ID DE TODOS LOS GUSANOS, Y EL ESTADO EN EL QUE ESTAN LOS GUSANOS
    // ESTADOS -> MOVIENDOSE, HACIENDO NADA, CAYENDO, LLEVANDO UNA DE 10 ARMAS

    //si se conecta un gusano nuevo, podria crear el worm y le pateo los managers, asi que ellos tienen el renderer :)
    if (!is_empty) {
        renderer.Clear();

        for (auto& worm : worms) {
            worm.second->render_new(Rect(0,0, 50, 50));   //esto va a tocar cambiarlo cuando tengamos las distintas acciones...
            worm.second->apply();
        }
    } else {    //SI NO RECIBO NADA, SEGUI EJECUTANDO LA ANTERIOR ANIMACION Y QUEDATE EN EL MISMO LUGAR
        renderer.Clear();

        map.draw_map();

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
    SdlWormTextureManager texture_manager(renderer);
    //LA CREACION DEL NUEVO GUSANO LA HARIA EN EL UPDATE_SCREEN, YA QUE ES DONDE HAGO EL POP
    // AHI RECIBIRIA EL MENSAJE DE CREAR NUEVO GUSANO :)
    worms[id_of_player] = new SdlWorm(texture_manager, sound_manager);
    
    while (is_running) {
        uint32_t frame_start;
        uint32_t frame_time;
        frame_start = SDL_GetTicks();
        is_running = main_loop(renderer, map);
        // sleep(1); conexion super lagueada
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time)
            SDL_Delay(frame_delay - frame_time);
    }
}