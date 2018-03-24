//
// Created by salach on 3/1/18.
//

#include "Box.h"
#include "Player.h"

Box::Box(Point pos, uint16_t pSizeX, uint16_t pSizeY, uint16_t rot) {
    this->sizeX = pSizeX;
    this->sizeY = pSizeY;
    this->position =pos;
    this->rotation = rot;
    this->imageName = "box.png";
}

float Box::resistMovement(Player *player) {
    return 0;
}