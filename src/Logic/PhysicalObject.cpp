//
// Created by salach on 3/1/18.
//

#include <cmath>
#include "PhysicalObject.h"

uint16_t PhysicalObject::getRotation() const {
    return rotation;
}

std::vector<Point>& PhysicalObject::getVerticesPosition() {
    return vertices;
}

PhysicalObject::~PhysicalObject() = default;

const std::string &PhysicalObject::getImageName() const {
    return imageName;
}

uint16_t PhysicalObject::getDiagonalLength() {
    return static_cast<uint16_t>(std::sqrt(sizeX * sizeX + sizeY * sizeY));
}

std::vector<Point> PhysicalObject::getCustomVerticesPosition(Point pos, uint16_t rot) {
    std::vector<Point> vertices = {
            Point( - sizeX/2,  - sizeY/2),
            Point(  sizeX/2,  - sizeY/2),
            Point(  sizeX/2,   sizeY/2),
            Point( - sizeX/2,   sizeY/2)
    };
    std::vector<Point> rotatedVertices;
    for (auto vertex : vertices){
        auto x = pos.getX() + vertex.getX()*cos(rot * M_PI / 180) - vertex.getY()*sin(rot * M_PI / 180);
        auto y = pos.getY() +  vertex.getX()*sin(rot * M_PI / 180) + vertex.getY()*cos(rot * M_PI / 180);
        rotatedVertices.emplace_back(x, y);
    }
    return rotatedVertices;
}

const Point &PhysicalObject::getPosition() const {
    return position;
}

void PhysicalObject::setInitialOrientation(const Point &pPosition, uint16_t pRotation) {
    if(position.isSet()){
        throw std::runtime_error( "Initial position already set!");
    }
    position = pPosition;
    rotation = pRotation;
    calculateVerticesPosition();
}

uint16_t PhysicalObject::getSizeX() const {
    return sizeX;
}

uint16_t PhysicalObject::getSizeY() const {
    return sizeY;
}

void PhysicalObject::calculateVerticesPosition() {
    vertices = getCustomVerticesPosition(position, rotation);
}
