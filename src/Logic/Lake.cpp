//
// Created by salach on 3/1/18.
//

#include "Lake.h"
#include "Player.h"

Lake::Lake(uint16_t pSizeX, uint16_t pSizeY, uint16_t posX, uint16_t posY, uint16_t rot){
    this->sizeX = pSizeX;
    this->sizeY = pSizeY;
    this->positionX =posX;
    this->positionY = posY;
    this->rotation = rot;
}

float Lake::resistMovement(Player *player) {
    return 0;
}

