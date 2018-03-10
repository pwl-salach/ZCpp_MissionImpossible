//
// Created by salach on 3/1/18.
//

#include "Box.h"
#include "Player.h"

Box::Box(uint16_t pSizeX, uint16_t pSizeY, uint16_t posX, uint16_t posY, uint16_t rot){
    this->sizeX = pSizeX;
    this->sizeY = pSizeY;
    this->positionX =posX;
    this->positionY = posY;
    this->rotation = rot;
}

float Box::resistMovement(Player *player) {
    return 0;
}