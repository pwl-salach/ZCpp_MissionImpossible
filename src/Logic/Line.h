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
    double calculate(double x);
    double getA() const;
    double getB() const;

protected:
    void calculateFactorA(const Point &first, const Point& second);
    void calculateFactorB(const Point &first, const Point& second);
    double onlyCalculateA(const Point &first, const Point& second) const;
    double a;
    double b;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_LINE_H
