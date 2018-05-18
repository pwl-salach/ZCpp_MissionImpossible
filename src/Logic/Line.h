//
// Created by Salach on 25.03.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_LINE_H
#define ZCPP_MISSIONIMPOSSIBLE_LINE_H


#include "Point.h"

class Line {
public:
    Line();
    Line(Point &first, Point &second);
    float calculate(float x);
    float getA() const;
    float getB() const;

protected:
    void calculateFactorA(const Point &first, const Point& second);
    void calculateFactorB(const Point &first, const Point& second);
    float onlyCalculateA(const Point &first, const Point& second) const;
    float a;
    float b;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_LINE_H
