//
// Created by Salach on 03.03.2018.
//

#include "Point.h"

Point::Point(uint16_t x, uint16_t y) : x(x), y(y) {}

uint16_t Point::getX() const {
    return x;
}

uint16_t Point::getY() const {
    return y;
}
