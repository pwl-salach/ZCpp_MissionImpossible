//
// Created by salach on 3/1/18.
//

#include <cmath>
#include "PhysicalObject.h"

uint16_t PhysicalObject::getRotation() const {
    return rotation;
}

std::vector<Point>  PhysicalObject::getVerticesPosition() {
    return getCustomVerticesPosition(position, rotation);
}

PhysicalObject::~PhysicalObject() = default;

const std::string &PhysicalObject::getImageName() const {
    return imageName;
}

uint16_t PhysicalObject::getDiagonalLength() {
    return static_cast<uint16_t>(sqrt(sizeX * sizeX + sizeY * sizeY));
}

std::vector<Point> PhysicalObject::getCustomVerticesPosition(Point position, uint16_t rotation) {
    std::vector<Point> vertices = {
            Point( - sizeX/2,  - sizeY/2),
            Point(  sizeX/2,  - sizeY/2),
            Point(  sizeX/2,   sizeY/2),
            Point( - sizeX/2,   sizeY/2)
    };
    std::vector<Point> rotatedVertices;
    for (auto vertex : vertices){
        auto x = position.getX() + vertex.getX()*cos(rotation * M_PI / 180) - vertex.getY()*sin(rotation * M_PI / 180);
        auto y = position.getY() +  vertex.getX()*sin(rotation * M_PI / 180) + vertex.getY()*cos(rotation * M_PI / 180);
        rotatedVertices.emplace_back(x, y);
    }
    return rotatedVertices;
}

const Point &PhysicalObject::getPosition() const {
    return position;
}

void PhysicalObject::setInitialPosition(const Point &pPosition) {
    if(position.isSet()){
        throw "Initial position already set!";
    }
    position = pPosition;
}

uint16_t PhysicalObject::getSizeX() const {
    return sizeX;
}

uint16_t PhysicalObject::getSizeY() const {
    return sizeY;
}
