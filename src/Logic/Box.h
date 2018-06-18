//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_BOX_H
#define ZCPP_MISSIONIMPOSSIBLE_BOX_H

#include "Obstacle.h"
#include "Player.h"
#include "Point.h"

class Box: public Obstacle{
public:
    Box(Point pPosition, uint16_t pSizeX, uint16_t pSizeY, uint16_t pRotation);

};


#endif //ZCPP_MISSIONIMPOSSIBLE_BOX_H
