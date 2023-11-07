
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;  // NOLINT

class SdlMap {
public:
    SdlMap(Renderer& renderer, Surface& image_floor1, Surface& image_floor2, Surface& image_floor3,
           Surface& image_water, Surface& image_background);

    void load_map(int arr[10][10]);
    void draw_map();

private:
    SDL_Rect src, dest;
    Texture floor1;
    Texture floor2;
    Texture floor3;
    Texture background;
    Texture water;
    Renderer& renderer;
    int map[10][10];
};
