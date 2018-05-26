//
// Created by salach on 3/2/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_OBSTACLE_H
#define ZCPP_MISSIONIMPOSSIBLE_OBSTACLE_H


#include "PhysicalObject.h"
#include "Player.h"

class Obstacle : virtual public PhysicalObject{
public:
    Obstacle(Point pPosition, uint16_t pSizeX, uint16_t pSizeY, uint16_t pRotation);

    bool blockingMovement();
    bool blockingView();

    Obstacle();
    enum Blocking{
        VIEW = 1,
        MOVEMENT = 2,
        BOTH = 3
    };

    virtual bool canBePassed();

protected:
    Blocking blocks;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_OBSTACLE_H
