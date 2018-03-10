//
// Created by salach on 3/1/18.
//

#include "PhysicalObject.h"

uint16_t PhysicalObject::getPositionX() const {
    return positionX;
}

uint16_t PhysicalObject::getPositionY() const {
    return positionY;
}

uint16_t PhysicalObject::getSizeX() const {
    return sizeX;
}

uint16_t PhysicalObject::getSizeY() const {
    return sizeY;
}

uint16_t PhysicalObject::getRotation() const {
    return rotation;
}

std::vector<Point>  PhysicalObject::getVerticesPosition() {
    std::vector<Point> vertices = {
            Point(this->getPositionX() - this->getSizeX()/2, this->getPositionY() + this->getSizeY()/2),
            Point(this->getPositionX() + this->getSizeX()/2, this->getPositionY() + this->getSizeY()/2),
            Point(this->getPositionX() - this->getSizeX()/2, this->getPositionY() - this->getSizeY()/2),
            Point(this->getPositionX() + this->getSizeX()/2, this->getPositionY() - this->getSizeY()/2)
    };
    return vertices;
}

PhysicalObject::~PhysicalObject() {

}
