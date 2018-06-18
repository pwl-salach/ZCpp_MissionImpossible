//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_LAKE_H
#define ZCPP_MISSIONIMPOSSIBLE_LAKE_H

#include "Obstacle.h"
#include "Player.h"

class Lake : public Obstacle {
public:
    Lake(Point pPosition, uint16_t pSizeX, uint16_t pSizeY, uint16_t pRotation);
};


#endif //ZCPP_MISSIONIMPOSSIBLE_LAKE_H
