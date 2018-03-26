//
// Created by Salach on 21.03.2018.
//

#include "Fence.h"

float Fence::resistMovement(Player *player) {
    return 0;
}

Fence::Fence(Point pos, uint16_t pSizeX, uint16_t rot) {
    position = pos;
    sizeX = pSizeX;
    rotation = rot;
    sizeY = 10;
    imageName = "fence.png";
}
