//
// Created by salach on 3/2/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_OBSTRACLE_H
#define ZCPP_MISSIONIMPOSSIBLE_OBSTRACLE_H


#include "PhysicalObject.h"

class Obstacle : public PhysicalObject{
protected:
    virtual float resistMovement() = 0;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_OBSTRACLE_H
