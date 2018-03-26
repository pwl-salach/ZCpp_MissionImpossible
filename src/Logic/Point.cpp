//
// Created by Salach on 03.03.2018.
//

#include <cmath>
#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {
    set = true;
}

double Point::getX() const {
    if(!isSet())
        throw "This point is not properly initiated!";
    return x;
}

double Point::getY() const {
    if(!isSet())
        throw "This point is not properly initiated!";
    return y;
}

bool Point::operator==(const Point &other) const {
    return sameXCoordinate(other) && sameYCoordinate(other);
}

bool Point::sameXCoordinate(const Point &other) const {
    return fabs(getX() - other.getX()) < fabs(getX()) * 0.001 || getX() == other.getX();
}

bool Point::sameYCoordinate(const Point &other) const{
    return fabs(getY() - other.getY()) < fabs(getY()) * 0.001 || getY() == other.getY();
}

Point::Point() {
    set = false;
}

bool Point::isSet() const {
    return set;
}

bool Point::closeTo(Point const &other, double threshold) const{
    return fabs(getX() - other.getX()) < threshold && fabs(getY() - other.getY()) < threshold;
}