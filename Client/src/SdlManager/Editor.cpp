#include "Editor.h"
#define FPS 30


MapEditor::MapEditor(std::string& map_name) : map_name(map_name) {

}

bool MapEditor::event_handler(SdlMap& sdl_map) {
        SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: {
                    sdl_map.save_to_file(map_name);
                    return false;
                }
                case SDLK_UP: {
                    angle++;
                    if (angle >= 360) {
                        angle = 360;
                    }
                    break;
                }
                case SDLK_DOWN: {
                    angle--;
                    if (angle  <= 0) {
                        angle = 0;
                    }
                    break;
                }
                case SDLK_w: {
                        camera.move(0, -3);
                        break;      
                }
                case SDLK_a: {
                        camera.move(-3,0);
                        break;
                }
                case SDLK_s: {
                        camera.move(0, 3);
                        break;
                }
                case SDLK_d: {
                        camera.move(3, 0);
                        break;
                }
                default : {
                        break;
                }
                
                
            }

        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_1:{ 
                    new_tile.type = '0';
                    break;
                }
                case SDLK_2:{
                    new_tile.type = '1';
                    break;
                }
                case SDLK_3:{
                        new_tile.type = '2';
                    
                    break;
                }
                case SDLK_F1:{
                        sdl_map.update_background("../Images/TerrainSprites/back1.png");
                    break;
                }
                case SDLK_F2:{
                        sdl_map.update_background("../Images/TerrainSprites/back2.png");
                    break;
                }
                case SDLK_F3:{
                        sdl_map.update_background("../Images/TerrainSprites/back3.png");
                    break;
                }
                case SDLK_z: {
                    if (!map.empty()) {
                        Tile element_to_pop = map.back();
                        if (element_to_pop.type == '2')
                            ammount_of_worms--;
                        map.pop_back();
                        sdl_map.update_map(map);
                        
                    }
                }
                default: {

                    break;
                }

            }
        } else if(event.type == SDL_MOUSEBUTTONDOWN) {

            switch(event.button.button) {
                
                case SDL_BUTTON_LEFT : {
                        if (!(new_tile.type == '2' && ammount_of_worms >= 8)) 
                            is_choosing = true;
                        else 
                            is_choosing = false;
                        
    
                        
                    break;
                }

                default: {
                    break;
                }
            }

        } else if (event.type == SDL_MOUSEBUTTONUP) {
            switch(event.button.button) {
                case SDL_BUTTON_LEFT : {
                    if (new_tile.pos_y > MAP_HEIGHT) {
                        is_choosing = false;
                        break;
                    }
                    if (is_choosing) {
                        map.emplace_back(new_tile);
                        sdl_map.update_map(map);
                    }

                    if (new_tile.type == '2' && ammount_of_worms < 8) 
                        ammount_of_worms++;

                    is_choosing = false;
                    
                    break;
                }
                default: {
                    break;
                }
                
            }

        }
    }
    if (is_choosing) {
        SDL_GetMouseState(&mouse_x, &mouse_y);
        new_tile.pos_x = mouse_x + camera.get_x();
        new_tile.pos_y = mouse_y + camera.get_y();
        new_tile.angle = angle;
        
    }
        


    return true;
}

bool MapEditor::main_loop(Renderer& renderer, SdlMap& sdl_map) {
        bool keep_playing = event_handler(sdl_map); 
        update_screen(renderer, sdl_map);

        return keep_playing;
}

void MapEditor::run() {
        const uint32_t frame_delay = 1000 / FPS;
        bool is_running = true;
        Window window("Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                  SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_SOFTWARE);
    camera.set_window(&window);
    SdlTexturesManager texture_manager(renderer, window, "../Images/TerrainSprites/back1.png");
    CommonMapParser parser;
    map = parser.get_map(map_name);
    SdlMap sdl_map(camera, map, texture_manager);
    if (!map.empty()) {
        ammount_of_worms = sdl_map.get_amount_of_worms();
        camera.focus_object(map.front().pos_x, map.front().pos_y);
    }
    
    while (is_running) {
        uint32_t frame_start;
        uint32_t frame_time;
        frame_start = SDL_GetTicks();
        is_running = main_loop(renderer, sdl_map);
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time)
            SDL_Delay(frame_delay - frame_time);
    }
}

void MapEditor::update_screen(Renderer& renderer, SdlMap& sdl_map) {
        renderer.Clear();
        sdl_map.draw_editor_map();
        if (is_choosing) {
            sdl_map.render_one(new_tile);
        }
        renderer.Present();
}

