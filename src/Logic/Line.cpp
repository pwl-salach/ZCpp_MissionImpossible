//
// Created by Salach on 25.03.2018.
//

#include "Line.h"

void Line::calculateFactorA(const Point &first, const Point &second) {
    int correction = 0;
    if (first.sameXCoordinate(second)) {
        correction = 1;
    }
    a = (first.getY() - second.getY()) / (first.getX() - second.getX() + correction);
}

void Line::calculateFactorB(const Point &first, const Point &second) {
    b = first.getY() - first.getX() * a;
}

float Line::calculate(float x) {
    return a * x + b;
}

Line::Line(Point &first, Point &second) {
    calculateFactorA(first, second);
    calculateFactorB(first, second);
}
