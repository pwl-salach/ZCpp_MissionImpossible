//
// Created by salach on 3/1/18.
//

#include "Person.h"

void Person::setPositionX(uint16_t posX) {
    this->positionX = posX;
}

void Person::setPositionY(uint16_t posY) {
    this->positionY = posY;
}

void Person::setRotation(uint16_t rot) {
    this->rotation = rot;
}

Person::Person() {
    this->sizeX = 30;
    this->sizeY = 18;
}
