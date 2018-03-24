//
// Created by salach on 3/2/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_OBSTRACLE_H
#define ZCPP_MISSIONIMPOSSIBLE_OBSTRACLE_H


#include "PhysicalObject.h"
#include "Player.h"

class Obstacle : public PhysicalObject{
public:
    enum Blocking{
        VIEW = 1,
        MOVEMENT = 2,
        BOTH = 3
    };
protected:
public:
    Obstacle();

protected:
    Blocking blocks;
    virtual float resistMovement(Player *player) = 0;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_OBSTRACLE_H
