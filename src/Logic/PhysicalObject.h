//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_PHYSICALOBJECT_H
#define ZCPP_MISSIONIMPOSSIBLE_PHYSICALOBJECT_H


#include <cstdint>
#include <map>

class PhysicalObject {
public:
    uint16_t getPositionX() const;

    uint16_t getPositionY() const;

    uint16_t getSizeX() const;

    uint16_t getSizeY() const;

    uint16_t getRotation() const;

    std::map<uint16_t, uint16_t> getVercitesPosition();

protected:
    uint16_t positionX;
    uint16_t positionY;
    uint16_t sizeX;
    uint16_t sizeY;
    uint16_t rotation;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_PHYSICALOBJECT_H
