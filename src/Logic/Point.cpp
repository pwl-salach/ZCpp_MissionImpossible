//
// Created by Salach on 03.03.2018.
//

#include <cmath>
#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {
    this->set = true;
}

double Point::getX() const {
    if(!this->isSet())
        throw "This point is not properly initiated!";
    return x;
}

double Point::getY() const {
    if(!this->isSet())
        throw "This point is not properly initiated!";
    return y;
}

bool Point::operator==(Point const &other) {
    return fabs(this->getX()-other.getX()) < this->getX()*0.001 && fabs(this->getY()-other.getY()) < this->getY()*0.001;
}

bool Point::sameXCoordinate(Point const &other) {
    return fabs(this->getX() - other.getX()) < this->getX() * 0.001;
}

bool Point::sameYCoordinate(Point const &other) {
    return fabs(this->getY() - other.getY()) < this->getY() * 0.001;
}

Point::Point() {
    this->set = false;
}

bool Point::isSet() const {
    return set;
}

bool Point::closeTo(Point const &other, double threshold) const{
    return fabs(this->getX() - other.getX()) < threshold && fabs(this->getY() - other.getY()) < threshold;
}
