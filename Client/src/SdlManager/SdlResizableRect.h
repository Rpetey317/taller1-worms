#pragma once
#include <SDL2pp/SDL2pp.hh>


using namespace SDL2pp;  // NOLINT

class SdlResizableRect {
public:
    SdlResizableRect();
    SdlResizableRect(int pos_x, int pos_y, int height, int width);
    void set_color(int red, int green, int blue);
    void set_delim_color(int red, int green, int blue);
    void set_position(int pos_x, int pos_y);
    void set_width(int width);
    void render(Renderer& renderer);
    void set_delim_position(int pos_x, int pos_y);
    void set_delim_width(int width);
    void set_height(int height);
    void set_delim_height(int height);

private:
    Color color;
    Color delim_color;
    Rect bar;
    Rect delim_bar;
    

};

    