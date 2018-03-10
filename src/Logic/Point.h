//
// Created by Salach on 03.03.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_POINT_H
#define ZCPP_MISSIONIMPOSSIBLE_POINT_H


#include <cstdint>

class Point {
public:
    Point(uint16_t x, uint16_t y);

    uint16_t getX() const;

    uint16_t getY() const;

private:
    uint16_t x;
    uint16_t y;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_POINT_H
