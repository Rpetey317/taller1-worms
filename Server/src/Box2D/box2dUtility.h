#ifndef BOX2D_UTILITY_H
#define BOX2D_UTILITY_H

#include "../../../Common/Vect2D.h"
#include "../../../libs/box2d/include/box2d/box2d.h"

b2Vec2 pixel_to_meter(Vect2D pixel) {
    return b2Vec2(pixel.x * 0.01f, (pixel.y * (-0.01f)) + 50.0f);
}

Vect2D meter_to_pixel(b2Vec2 meter) {
    return Vect2D(static_cast<int>(meter.x * 100.0f), static_cast<int>(meter.y * 100.0f));
}

#endif 
