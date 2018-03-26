//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_PHYSICALOBJECT_H
#define ZCPP_MISSIONIMPOSSIBLE_PHYSICALOBJECT_H


#include <cstdint>
#include <map>
#include <vector>
#include "Point.h"

class PhysicalObject {
public:
    const Point &getPosition() const;

    void setInitialPosition(const Point &position);

    virtual ~PhysicalObject() = 0;

    uint16_t getRotation() const;

    uint16_t getSizeX() const;

    uint16_t getSizeY() const;

    const std::string &getImageName() const;

    std::vector<Point> getVerticesPosition();

    std::vector<Point> getCustomVerticesPosition(Point position, uint16_t rotation);

    uint16_t getDiagonalLength();

protected:
public:
    PhysicalObject();

protected:
    Point position;
    uint16_t sizeX;
    uint16_t sizeY;
    uint16_t rotation;
    std::string imageName;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_PHYSICALOBJECT_H
