//
// Created by salach on 3/2/18.
//

#include "Obstacle.h"

Obstacle::Obstacle() {}

Obstacle::Obstacle(Point pPosition, uint16_t pSizeX, uint16_t pSizeY, uint16_t pRotation) {
    position = pPosition;
    sizeX = pSizeX;
    sizeY = pSizeY;
    rotation = pRotation;
    calculateVerticesPosition();
}
