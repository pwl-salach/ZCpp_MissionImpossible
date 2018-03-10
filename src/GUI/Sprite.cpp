//
// Created by salach on 3/2/18.
//

#include "Sprite.h"
#include "../Utils/FileManager.h"

Sprite::Sprite(PhysicalObject *pObject, const std::string &fileName) {
    this->object = pObject;
    this->surface = FileManager::loadImage(fileName);
}

const SDL_Point & Sprite::getCenter(){
    this->center.x = this->object->getPositionX();
    this->center.y = this->object->getPositionY();
    return center;
}

const SDL_Rect & Sprite::getVerticesPositions() {
    calculateVerticesPositions();
    return this->verticesPositions;
}

double Sprite::getAngle() const {
    return this->object->getRotation();
}

void Sprite::calculateVerticesPositions() {
    this->verticesPositions.x = this->object->getPositionX() - this->object->getSizeX()/2;
    this->verticesPositions.y = this->object->getPositionY() - this->object->getSizeY()/2;
    this->verticesPositions.w = this->object->getSizeX();
    this->verticesPositions.h = this->object->getSizeY();
}
