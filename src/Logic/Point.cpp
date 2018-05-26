//
// Created by Salach on 03.03.2018.
//

#include <cmath>
#include <stdexcept>
#include "Point.h"

Point::Point(float x, float y) : x(x), y(y) {
    set = true;
}

float Point::getX() const {
    if(!isSet())
        throw std::runtime_error( "This point is not properly initiated!");
    return x;
}

float Point::getY() const {
    if(!isSet())
        throw std::runtime_error( "This point is not properly initiated!");
    return y;
}

bool Point::operator==(const Point &other) const {
    return sameXCoordinate(other) && sameYCoordinate(other);
}

bool Point::sameXCoordinate(const Point &other) const {
    return std::fabs(getX() - other.getX()) < std::fabs(getX()) * 0.001 || getX() == other.getX();
}

bool Point::sameYCoordinate(const Point &other) const{
    return std::fabs(getY() - other.getY()) < std::fabs(getY()) * 0.001 || getY() == other.getY();
}

Point::Point() {
    set = false;
}

bool Point::isSet() const {
    return set;
}