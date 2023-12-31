#include "SdlCamera.h"


SdlCamera::SdlCamera() {}

void SdlCamera::set_window(Window* window) {
        this->window = window;
        camera.SetX(window->GetWidth()/2);
        camera.SetY(window->GetHeight()/2);
        camera.SetW(window->GetWidth()/2);
        camera.SetH(window->GetHeight()/2);
}

void SdlCamera::move(int x, int y) {
        camera.SetX(camera.GetX() + x);
        camera.SetY(camera.GetY() + y);
}

void SdlCamera::focus_object(int x, int y) {
        camera.SetX(x - camera.GetW());
        camera.SetY(y - camera.GetH());
}

void SdlCamera::update_position() {
        
}

int SdlCamera::get_window_height() {
        return window->GetHeight();
}

int SdlCamera::get_window_width() {
        return window->GetWidth();
}

int SdlCamera::get_x() {
        return camera.GetX();
}

int SdlCamera::get_y() {
        return camera.GetY();
}

int SdlCamera::get_height() {
        return camera.GetH();
}

int SdlCamera::get_width() {
        return camera.GetW();
}
