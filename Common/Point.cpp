#include "Point.h"

#include <iostream>

Point::Point(int x, int y): x(x), y(y) {}

Point::Point(): x(0), y(0) {}

Point::Point(Point const& other): x(other.x), y(other.y) {}

Point Point::above() {
    Point ans(this->x, this->y - 1);
    return ans;
}

Point Point::below() {
    Point ans(this->x, this->y + 1);
    return ans;
}

Point Point::right() {
    Point ans(this->x + 1, this->y);
    return ans;
}

Point Point::left() {
    Point ans(this->x - 1, this->y);
    return ans;
}


Point Point::operator+(Point const& other) {
    Point ans(this->x + other.x, this->y + other.y);
    return ans;
}

Point Point::operator-(Point const& other) {
    Point ans(this->x - other.x, this->y - other.y);
    return ans;
}

Point& Point::operator=(const Point& other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
}

void Point::print() { std::cout << this->x << " " << this->y << std::endl; }
