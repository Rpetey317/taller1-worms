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


void SdlWormTextureManager::render(int worm_state, int animation_phase, int x_pos, int y_pos, SDL_RendererFlip flip) {
    if (worm_state == 0) {  //crear clase worm_state
        
        renderer.Copy(*texture_map["STATIC"], Rect(0, 60 * animation_phase, 50, 50), Rect(x_pos, y_pos, 50, 50), 0, NullOpt, flip);

    } else {
        renderer.Copy(*texture_map["WALK"], Rect(0, 60 * animation_phase, 50, 50), Rect(x_pos, y_pos, 50, 50), 0, NullOpt, flip);
    } 
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
    //renderer.Copy(worm.sprite, Rect(src_x, src_y, 50, 50), Rect(worm.x_pos, worm.y_pos, 50, 50),
    //                  0, NullOpt, worm.flip);
    texture_manager.render(worm_state, animation_phase, x_pos, y_pos, flip);
}

void SdlWorm::render_new(Rect rect) {

}

SdlWorm::SdlWorm(SdlWormTextureManager& texture_manager, SdlSoundManager& sound_manager) : texture_manager(texture_manager), sound_manager(sound_manager) {
    x_pos = 0;
    y_pos = 0;
    animation_phase = 0;
    worm_state = 0;
    flip = SDL_FLIP_NONE;
}
void SdlWorm::destroy() {
    sound_manager.destroy();
}

void SdlWorm::play_sound(std::string sound_to_play) {
    sound_manager.play_sound(sound_to_play);
}

void SdlWorm::next_animation() {
    
    animation_phase = animation_phase + 1;
    if (worm_state == 0) {
        if (animation_phase >= 6) 
            animation_phase = 0;
        
    } else if (worm_state == 1) {
        
        if (animation_phase >= 14)
            animation_phase = 0;
    }
    
}

SdlManager::SdlManager(Queue<int>& commands, Queue<std::vector<int>>& positions):
        commands(commands), positions(positions) {
    // Initialize SDL library
    // SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    // Initialize SDL_ttf library
    SDLTTF ttf;
}

bool SdlManager::event_handler() {
//VAMOS A ELEGIR ARMA CON NUMEROS 0 AL 9, YA QUE HAY 10 ARMAS :)
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            worms[0]->destroy();
            return false;
        } else if (event.type == SDL_KEYDOWN) {

            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: {
                    worms[0]->destroy();
                    commands.push(0);
                    return false;
                }
                case SDLK_RIGHT: {
                    worms[0]->worm_state = 1;
                    worms[0]->flip = SDL_FLIP_HORIZONTAL;
                    
                    commands.push(1);
                    break;
                }
                case SDLK_LEFT: {
                    worms[0]->worm_state = 1;
                    worms[0]->flip = SDL_FLIP_NONE;
                    commands.push(2);
                    break;
                } break;
            }

        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_RIGHT: {
                    worms[0]->worm_state = 0;
                    worms[0]->animation_phase = 0;
                    commands.push(3);
                    break;
                }
                case SDLK_LEFT: {
                    worms[0]->worm_state = 0;
                    worms[0]->animation_phase = 0;
                    commands.push(3);
                    break;
                }
                case SDLK_0:{ //BAZOOKA
                    break;
                }
                case SDLK_1:{//MORTERO
                    break;
                }
                case SDLK_2:{//GRANDA ROJA
                    break;
                }
                case SDLK_3:{//GRANADA VERDE
                    break;
                }
                case SDLK_4:{//BANANA
                    break;
                }
                case SDLK_5:{//GRANADA SANTA
                    break;
                }
                case SDLK_6:{//ATAQUE AEREO
                    break;
                }
                case SDLK_7:{//DINAMITA
                    break;
                }
                case SDLK_8:{//BATE DE BEISBOL
                    break;
                }
                case SDLK_9:{//TELETRANSPORTACION
                    break;
                }
                case SDLK_RETURN: { //SALTO HACIA DELANTE
                    commands.push(4);
                    break;
                }
                case SDLK_BACKSPACE: {  //SALTO HACIA ATRAS
                    commands.push(5);
                    break;
                }
                default: {

                    break;
                }

            }
        } else if(event.type == SDL_MOUSEBUTTONDOWN) {
            switch(event.button.button) {
                case SDL_BUTTON_LEFT : {
                    //ACA SETEO GUSANO EN "CARGANDO ARMA", Y A CADA TICK LE SUMO UNO EL PODER
                    worms[0]->play_sound("CHARGE");
                    break;
                } 
                default: {
                    break;
                }
            }

        } else if (event.type == SDL_MOUSEBUTTONUP) {
            switch(event.button.button) {
                case SDL_BUTTON_LEFT : {
                    //Y ACA SETEO AL GUSANO EN "DISPARO", TERMINARIA EL TURNO Y PUSHEO A LA QUEUE EL DISPARO
                    //ACA OBTENGO DIRECCION DISPARO, PUEDO OBTENER LA POSICION X E Y DE DONDE ESTA MI MOUSE, LA DEL GUSANO 
                    // ANGULO ->
                    double opuesto = abs(worms[0]->y_pos - event.button.y);
                    double adyacente = abs(worms[0]->x_pos - event.button.x);
                    double angulo = atan(opuesto/adyacente);
                    std::cout << angulo << std::endl;
                    worms[0]->play_sound("THROWING");
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
    worms[0] = new SdlWorm(texture_manager, sound_manager);
    
    worms[0]->x_pos = 50;
    worms[0]->y_pos = 50;
    worms[0]->animation_phase = 0;
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
    positions.try_pop(val);
    //int src_x = 0, src_y = 0;
    //si se conecta un gusano nuevo, podria crear el worm y le pateo los managers, asi que ellos tienen el renderer :)
    if (!val.empty()) {
        renderer.Clear();
        //src_x = 0;
        //src_y = 60;
        for (auto& worm : worms) {
            worm.second->render_new(Rect(val[0], val[1], 50, 50));   //esto va a tocar cambiarlo cuando tengamos las distintas acciones...
        }
    } else {    //SI NO RECIBO NADA, SEGUI EJECUTANDO LA ANTERIOR ANIMACION Y QUEDATE EN EL MISMO LUGAR
        renderer.Clear();

        map.draw_map();

        //src_x = 0;
        //src_y = 60 * worms[0]->animation_phase;
        //renderer.Copy(worm.sprite, Rect(src_x, src_y, 50, 50), Rect(worm.x_pos, worm.y_pos, 50, 50),
        //              0, NullOpt, worm.flip);
        for (auto& worm : worms) {
            worm.second->render_same();
            worm.second->next_animation();
        }
    }

    renderer.Present();
}

int main() {
    Queue<int> commands;
    Queue<std::vector<int>> positions;
    
    SdlManager manager(commands, positions);

    manager.run("../../../Images/TerrainSprites/back1.png", "../../../maps/mapita.txt");
}
