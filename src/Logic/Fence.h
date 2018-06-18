//
// Created by Salach on 21.03.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_FENCE_H
#define ZCPP_MISSIONIMPOSSIBLE_FENCE_H


#include "Obstacle.h"

class Fence: public Obstacle {
public:
    Fence(Point pPosition, uint16_t pSizeX, uint16_t pRotation);

};

#endif //ZCPP_MISSIONIMPOSSIBLE_FENCE_H
