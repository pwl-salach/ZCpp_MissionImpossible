//
// Created by Salach on 21.03.2018.
//

#include "Fence.h"

Fence::Fence(Point pPosition, uint16_t pSizeX, uint16_t pRotation):Obstacle(pPosition, pSizeX, 10, pRotation) {
    imageName = "fence.png";
}
