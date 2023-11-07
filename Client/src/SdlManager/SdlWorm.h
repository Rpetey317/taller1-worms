

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLImage.hh>
using namespace SDL2pp;  // NOLINT

class SdlWorm {
public:
    int x_pos;
    int y_pos;
    int animation_phase;
    SDL_RendererFlip flip;
    Texture& sprite;
    explicit SdlWorm(Texture& sprite);
    void next_animation();

private:
};
