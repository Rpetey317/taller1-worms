#pragma once
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;  // NOLINT

class SdlCamera {

        public:
                SdlCamera();
                void update_position();
                void focus_object(int x, int y);
                int get_x();
                int get_y();
                void set_window(Window *window);

        private:
                Rect camera;
                Window* window;



};