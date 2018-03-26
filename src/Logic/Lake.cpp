//
// Created by salach on 3/1/18.
//

#include "Lake.h"
#include "Player.h"

Lake::Lake(Point pos, uint16_t pSizeX, uint16_t pSizeY, uint16_t rot) {
    position = pos;
    sizeX = pSizeX;
    sizeY = pSizeY;
    rotation = rot;
    imageName = "lake.png";
}

float Lake::resistMovement(Player *player) {
    return 0;
}

