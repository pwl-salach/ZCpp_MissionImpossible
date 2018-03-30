//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_PERSON_H
#define ZCPP_MISSIONIMPOSSIBLE_PERSON_H


#include <cstdint>
#include "PhysicalObject.h"
#include "Point.h"

/*!
 * \brief
 */
class Person : virtual public PhysicalObject{
public:
    enum Movement{
        NONE = 0,
        FORWARD = 1,
        BACK = 2,
        TURN_LEFT = 3,
        TURN_RIGHT = 4
    };
    Person();

    ~Person() override;
    void move();
    Point calculateNewPosition(uint16_t rot);
    uint16_t calculateNewRotation();

    void setRotation(uint16_t rot);

    void setMovement(Movement movement);

    void setTurning(Movement turning);

protected:
    Movement movement;
    Movement turning;
    uint8_t movementSpeed;
    uint8_t turningSpeed;
    Point calculateNewPosition();
};


#endif //ZCPP_MISSIONIMPOSSIBLE_PERSON_H
