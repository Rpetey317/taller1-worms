#include "SdlResizableRect.h"

SdlResizableRect::SdlResizableRect() {}

SdlResizableRect::SdlResizableRect(int pos_x, int pos_y, int height, int width) {
        bar.SetX(pos_x);
        bar.SetY(pos_y);
        bar.SetH(height);
        bar.SetW(width);
        delim_bar.SetX(pos_x);
        delim_bar.SetY(pos_y);
        delim_bar.SetH(height);
        delim_bar.SetW(width);        
}

void SdlResizableRect::set_width(int width) {
        bar.SetW(width);
}

void SdlResizableRect::set_delim_width(int width) {
        delim_bar.SetW(width);
}

void SdlResizableRect::set_color(int red, int green, int blue) {
        color.SetRed(red);
        color.SetGreen(green);
        color.SetBlue(blue);
}

void SdlResizableRect::set_delim_color(int red, int green, int blue) {
        delim_color.SetRed(red);
        delim_color.SetGreen(green);
        delim_color.SetBlue(blue);
}

void SdlResizableRect::set_position(int pos_x, int pos_y) {
        bar.SetX(pos_x);
        bar.SetY(pos_y);
}

void SdlResizableRect::set_delim_position(int pos_x, int pos_y) {
        delim_bar.SetX(pos_x);
        delim_bar.SetY(pos_y);
}

void SdlResizableRect::set_height(int height) {
        bar.SetH(height);
}

void SdlResizableRect::set_delim_height(int height) {
        delim_bar.SetH(height);
}

void SdlResizableRect::render(Renderer& renderer) {
        renderer.SetDrawColor(delim_color);
        renderer.DrawRect(delim_bar);
        renderer.SetDrawColor(color);
        renderer.FillRect(bar);
}
