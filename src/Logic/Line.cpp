//
// Created by Salach on 25.03.2018.
//

#include "Line.h"
#include <stdexcept>

void Line::calculateFactorA(const Point &first, const Point &second) {
    a = onlyCalculateA(first, second);
}

void Line::calculateFactorB(const Point &first, const Point &second) {
    b = first.getY() - first.getX()*a;
}

float Line::onlyCalculateA(const Point &first, const Point &second) const {
    int correction = 0;
    if(first.sameXCoordinate(second)){
        correction = 1;
        //throw std::runtime_error( "X coordinates are the same for those points");
    }
    return (first.getY() - second.getY())/(first.getX() - second.getX() + correction);
}

float Line::calculate(float x) {
    return a*x + b;
}

Line::Line(Point &first, Point &second) {
    calculateFactorA(first, second);
    calculateFactorB(first, second);
}

float Line::getA() const {
    return a;
}

float Line::getB() const {
    return b;
}

Line::Line() {

}
