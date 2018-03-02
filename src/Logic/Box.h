//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_BOX_H
#define ZCPP_MISSIONIMPOSSIBLE_BOX_H

#include "Obstacle.h"

class Box: public Obstacle{
public:
    Box(uint16_t pSizeX, uint16_t pSizeY, uint16_t posX, uint16_t posY, uint16_t rot);

protected:
    float resistMovement() override;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_BOX_H
