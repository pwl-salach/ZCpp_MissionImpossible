//
// Created by Salach on 21.03.2018.
//

#include "Fence.h"

float Fence::resistMovement(Player *player) {
    return 0;
}

Fence::Fence(Point pos, uint16_t pSizeX, uint16_t rot) {
    this->position = pos;
    this->sizeX = pSizeX;
    this->rotation = rot;
    this->sizeY = 10;
    this->imageName = "fence.png";
}
