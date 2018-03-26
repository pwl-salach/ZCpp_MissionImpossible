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
    bool operator==(const Point &other) const;
    double getX() const;
    double getY() const;
    bool isSet() const;
    bool sameXCoordinate(const Point &other) const;
    bool sameYCoordinate(const Point &other) const;
    bool closeTo(Point const &other, double threshold) const;

private:
    double x;
    double y;
    bool set;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_POINT_H
