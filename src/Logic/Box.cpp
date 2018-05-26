//
// Created by salach on 3/1/18.
//

#include "Box.h"
#include "Player.h"

Box::Box(Point pPosition, uint16_t pSizeX, uint16_t pSizeY, uint16_t pRotation)
        :Obstacle(pPosition, pSizeX, pSizeY, pRotation) {
    imageName = "box.png";
    blocks = Blocking::BOTH;
}