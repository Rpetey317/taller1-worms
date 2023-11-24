#include "Vect2D.h"

#include <iostream>

Vect2D::Vect2D(int x, int y): x(x), y(y) {}

Vect2D::Vect2D(): x(0), y(0) {}

Vect2D::Vect2D(Vect2D const& other): x(other.x), y(other.y) {}

Vect2D Vect2D::above() {
    Vect2D ans(this->x, this->y - 1);
    return ans;
}

Vect2D Vect2D::below() {
    Vect2D ans(this->x, this->y + 1);
    return ans;
}

Vect2D Vect2D::right() {
    Vect2D ans(this->x + 1, this->y);
    return ans;
}

Vect2D Vect2D::left() {
    Vect2D ans(this->x - 1, this->y);
    return ans;
}


Vect2D Vect2D::operator+(Vect2D const& other) {
    Vect2D ans(this->x + other.x, this->y + other.y);
    return ans;
}

Vect2D Vect2D::operator-(Vect2D const& other) {
    Vect2D ans(this->x - other.x, this->y - other.y);
    return ans;
}

Vect2D& Vect2D::operator=(const Vect2D& other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
}

void Vect2D::print() { std::cout << this->x << " " << this->y << std::endl; }
