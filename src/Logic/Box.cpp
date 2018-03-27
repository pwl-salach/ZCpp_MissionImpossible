//
// Created by salach on 3/1/18.
//

#include "Box.h"
#include "Player.h"

Box::Box(Point pos, uint16_t pSizeX, uint16_t pSizeY, uint16_t rot) {
    sizeX = pSizeX;
    sizeY = pSizeY;
    position = pos;
    rotation = rot;
    imageName = "box.png";
}