//
// Created by salach on 3/1/18.
//

#include "Lake.h"
#include "Player.h"

Lake::Lake(Point pos, uint16_t pSizeX, uint16_t pSizeY, uint16_t rot) {
    this->position = pos;
    this->sizeX = pSizeX;
    this->sizeY = pSizeY;
    this->rotation = rot;
    this->imageName = "lake.png";
}

float Lake::resistMovement(Player *player) {
    return 0;
}

