//
// Created by salach on 3/1/18.
//

#include "Lake.h"
#include "Player.h"

Lake::Lake(Point pPosition, uint16_t pSizeX, uint16_t pSizeY, uint16_t pRotation)
        :Obstacle(pPosition, pSizeX, pSizeY, pRotation) {
    imageName = "lake.png";
}
