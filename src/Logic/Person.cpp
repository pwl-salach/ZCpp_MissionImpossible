//
// Created by salach on 3/1/18.
//

#include "Person.h"

void Person::setRotation(uint16_t rot) {
    this->rotation = rot;
}

Person::Person() {
    this->sizeX = 30;
    this->sizeY = 18;
}

void Person::setPosition(const Point &point) {
    this->positionX = point.getX();
    this->positionY = point.getY();
}
Person::~Person() {}

