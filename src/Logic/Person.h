//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_PERSON_H
#define ZCPP_MISSIONIMPOSSIBLE_PERSON_H


#include <cstdint>
#include "PhysicalObject.h"
#include "FieldOfView.h"
#include "Point.h"

/*!
 * \brief
 */
class Person : public PhysicalObject{
public:
    enum Movement{
        NONE = 0,
        FORWARD = 1,
        BACK = 2,
        TURN_LEFT = 3,
        TURN_RIGHT = 4
    };
    Person();
    virtual ~Person()=0;
    void move();
    Point calculateNewPosition(const Movement &movement);
    void setPosition(const Point &point);
    void setRotation(uint16_t rot);

protected:
    void turn(const Movement &movement);
    Movement movement;
    uint8_t movementSpeed;
    uint8_t turningSpeed;
    FieldOfView *fov;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_PERSON_H
