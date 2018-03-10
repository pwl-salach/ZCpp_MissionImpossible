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
        FORWARD = 0,
        BACK = 1,
        TURN_LEFT = 2,
        TURN_RIGHT = 3
    };
    Person();
    virtual ~Person()=0;
    void move(const Movement &movement);
    void turn(const Movement &movement);
    Point calculateNewPosition(const Movement &movement);
    void setPosition(const Point &point);
    void setRotation(uint16_t rot);

protected:
    uint8_t movementSpeed;
    uint8_t turningSpeed;
    FieldOfView *fov;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_PERSON_H
