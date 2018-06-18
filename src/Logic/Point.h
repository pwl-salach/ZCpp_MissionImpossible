//
// Created by Salach on 03.03.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_POINT_H
#define ZCPP_MISSIONIMPOSSIBLE_POINT_H


#include <cstdint>

class Point {
public:
    Point();

    Point(float x, float y);

    bool operator==(const Point &other) const;

    float getX() const;

    float getY() const;

    bool isSet() const;

    bool sameXCoordinate(const Point &other) const;

    bool sameYCoordinate(const Point &other) const;

private:
    float x;
    float y;
    bool set;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_POINT_H
