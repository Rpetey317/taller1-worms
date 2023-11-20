#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include <tgmath.h>
#include <unistd.h>
#include "SdlManager.h"
#define FPS 15


using namespace SDL2pp;  // NOLINT


CommonMapParser::CommonMapParser() {}

std::vector<Tile> CommonMapParser::get_map(std::string file_name) {

        std::fstream archivo(file_name);
        std::vector<Tile> map;
        char scape;
        char type = ' ';
        char angle[4];
        char pos_x[5];
        char pos_y[5];
        while(!archivo.eof()) {
            archivo.get(type);
            archivo.get(scape);
            archivo.get(angle[0]);
            archivo.get(angle[1]);
            archivo.get(angle[2]);
            angle[3] = 0;
            archivo.get(scape);
            archivo.get(pos_x[0]);
            archivo.get(pos_x[1]);
            archivo.get(pos_x[2]);
            archivo.get(pos_x[3]);
            pos_x[4] = 0;
            archivo.get(scape);
            archivo.get(pos_y[0]);
            archivo.get(pos_y[1]);
            archivo.get(pos_y[2]);
            archivo.get(pos_y[3]);
            pos_y[4] = 0;
            archivo.get(scape);
            Tile tile = {type, atoi(angle), atoi(pos_x), atoi(pos_y)};
            map.emplace_back(tile);
        }

    return map;
}


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

SdlMap::SdlMap(std::vector<Tile> map, SdlTexturesManager& textures_manager) : map(map), textures_manager(textures_manager) {}

void SdlTexturesManager::draw_background() {
    SDL_Rect src,dest;
    src.x = src.y = dest.x = dest.y = 0;
    src.w = dest.w = window.GetWidth();
    src.h = dest.h = window.GetHeight();
    renderer.Copy(background, src,dest);
}

SdlTexturesManager::SdlTexturesManager(Renderer& renderer, Window& window, std::string background_type) :
 renderer(renderer), window(window),small_bridge(renderer, "../../../Images/TerrainSprites/bridge.png"), large_bridge(renderer, "../../../Images/TerrainSprites/large-bridge.png"), water(renderer, "../../../Images/Worms/wblink1.png"), background(renderer, background_type) {
    
    src.x = src.y = 0;
    src.h = dest.h = 19;
}

void SdlTexturesManager::draw(Tile& tile) {
    switch (tile.type) {
        case '0':
            src.w = dest.w = 64;
            dest.x = tile.pos_x;
            dest.y = tile.pos_y;
            renderer.Copy(small_bridge, src, dest, tile.angle, NullOpt, 0);
            break;
        case '1':
            src.w = dest.w = 128;
            dest.x = tile.pos_x;
            dest.y = tile.pos_y;
            renderer.Copy(large_bridge, src, dest, tile.angle, NullOpt, 0);
            break;
        default:
            break;
    }
    
}

void SdlMap::draw_map() {
        textures_manager.draw_background();
    for (auto& tile : map) 
        textures_manager.draw(tile);
}

void SdlWorm::render_same() {
    texture_manager.render(worm_state, animation_phase, x_pos, y_pos, flip);
}

void SdlWorm::render_new(Rect rect) {

}

void SdlWorm::apply() {
    if (is_charging) { 
        attack_power = attack_power + 1;
        if (attack_power == 100) {
            attack_power = 100;
        }
    }
}

SdlWorm::SdlWorm(SdlWormTextureManager& texture_manager, SdlSoundManager& sound_manager) : texture_manager(texture_manager), sound_manager(sound_manager) {
    x_pos = 50;
    y_pos = 50;
    animation_phase = 0;
    flip = SDL_FLIP_NONE;
    attack_power = 0;
    worm_state = new SdlWormStateStill();
}
void SdlWorm::destroy() {
    sound_manager.destroy();
}

void SdlWorm::play_sound(std::string sound_to_play) {
    sound_manager.play_sound(sound_to_play);
}

void SdlWorm::next_animation() {
    
    animation_phase = animation_phase + 1;
    if (worm_state->is_at_max_animation_phase(animation_phase)) {
        animation_phase = 0;
    } 
    
}

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
                    commands.push(0);
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
                    commands.push(6);
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



SdlSoundManager::SdlSoundManager() : mixer(44100, MIX_DEFAULT_FORMAT, 2, 2048), background_music("../../../Images/background.wav")
{
    mixer.PlayMusic(background_music, -1);
    sound_map["CHARGE"] = new Chunk("../../../Images/tuki.wav"); 
    sound_map["THROWING"] = new Chunk("../../../Images/charge.wav");
}

void SdlSoundManager::play_sound(std::string sound_to_play) {
try {

    mixer.PlayChannel(-1, *sound_map[sound_to_play], 0);
} catch (Exception& err) {
    mixer.HaltChannel(-1);  //si hay demasiados sonidos -> quitalos todos
}

}

void SdlSoundManager::destroy() {
    for (auto chunk : sound_map) {
        delete chunk.second;
    }
    
}

void SdlManager::run(std::string background_type, std::string selected_map) {
    //QUIZA LA IDEA ES QUE TENGA ACA UN POP PARA RECIBIR ESTE BACKGROUND_TYPE Y SELECTED_MAP???
    //COMO HACEMOS TEMA ANIMACIONES ENTRE MUCHOS PLAYERS???
    //TENGO UNA IDEA, ADEMAS DE RECIBIR POSICIONES GUSANOS, RECIBO SUS ID Y QUE ACCION REALIAZARON
    //SI ACCION ANTERIOR == LA QUE RECIBO -> EJECUTA PROX ANIMACION. SI ACCION ANTERIOR =/= LA QUE RECIBO, CAMBIO A ESA NUEVA ANIMACION :)
    //EL ID DEL PLAYER QUIZA LO RECIBO POR ACA O POR UNA QUEUE?
    const int frame_delay = 1000 / FPS;
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

void SdlManager::update_screen(Renderer& renderer, SdlMap& map) {
    std::vector<int> val;
    ingoing.try_pop(val);
    // LAS POSICIONES DE TODOS LOS GUSANOS, EL ID DE TODOS LOS GUSANOS, Y EL ESTADO EN EL QUE ESTAN LOS GUSANOS
    // ESTADOS -> MOVIENDOSE, HACIENDO NADA, CAYENDO, LLEVANDO UNA DE 10 ARMAS

    //si se conecta un gusano nuevo, podria crear el worm y le pateo los managers, asi que ellos tienen el renderer :)
    if (!val.empty()) {
        renderer.Clear();

        for (auto& worm : worms) {
            worm.second->render_new(Rect(val[0], val[1], 50, 50));   //esto va a tocar cambiarlo cuando tengamos las distintas acciones...
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

/*int main() {
    Queue<int> commands;
    Queue<std::vector<int>> positions;
    
    SdlManager manager(commands, positions, 0);

    manager.run("../../../Images/TerrainSprites/back1.png", "../../../maps/mapita.txt");
}*/


SdlWormState::~SdlWormState() {}

SdlWormState::SdlWormState(){}

SdlWormStateBazooka::SdlWormStateBazooka(){}
SdlWormStateStill::SdlWormStateStill(){}
SdlWormStateWalk::SdlWormStateWalk(){}

bool SdlWormStateStill::is_at_max_animation_phase(int animation_phase) {
    return animation_phase == 6;
}

bool SdlWormStateBazooka::is_at_max_animation_phase(int animation_phase) {
    return animation_phase == 6;
}

bool SdlWormStateWalk::is_at_max_animation_phase(int animation_phase) {
    return animation_phase == 14;
}



void SdlWormStateStill::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    renderer.Copy(*texture_map["STATIC"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
}

void SdlWormStateBazooka::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    renderer.Copy(*texture_map["BAZOOKA"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
}

void SdlWormStateWalk::render(Renderer& renderer, std::map<std::string, Texture*>& texture_map, Rect& dest, SDL_RendererFlip& flip, int animation_phase) {
    renderer.Copy(*texture_map["WALK"], Rect(0, 60 * animation_phase, 50, 50), dest, 0, NullOpt, flip);
}
