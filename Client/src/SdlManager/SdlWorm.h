

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;  // NOLINT

class SdlWorm {
public:
    int x_pos;
    int y_pos;
    int animation_phase;
    explicit SdlWorm(Texture& sprite);
    Texture& sprite;
    void next_animation();

private:
};
