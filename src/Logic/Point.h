//
// Created by Salach on 03.03.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_POINT_H
#define ZCPP_MISSIONIMPOSSIBLE_POINT_H


#include <cstdint>

class Point {
public:
    Point();
    Point(double x, double y);
    bool operator==(Point const &other);
    bool sameXCoordinate(Point const &other);
    bool sameYCoordinate(Point const &other);
    double getX() const;
    double getY() const;
    bool closeTo(Point const &other, double threshold) const;
    bool isSet() const;

private:
    double x;
    double y;
    bool set;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_POINT_H
