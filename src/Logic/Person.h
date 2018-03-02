//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_PERSON_H
#define ZCPP_MISSIONIMPOSSIBLE_PERSON_H


#include <cstdint>
#include "PhysicalObject.h"

class Person :public PhysicalObject{
public:
    void setPositionX(uint16_t posX);
    void setPositionY(uint16_t posY);
    void setRotation(uint16_t rot);
protected:
public:
    Person();

protected:
    void moveForward();
    void moveBack();
    void turnRight();
    void turnLeft();
    uint8_t movementSpeed;
    uint8_t turningSpeed;
private:
    uint8_t turnStep;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_PERSON_H
