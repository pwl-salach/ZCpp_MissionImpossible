//
// Created by salach on 3/2/18.
//

#include "Sprite.h"
#include "../Utils/FileManager.h"

Sprite::Sprite(PhysicalObject *pObject) {
    this->object = pObject;
    this->surface = FileManager::loadImage(object->getImageName());
}

const SDL_Point & Sprite::getCenter(){
    this->center.x = (int)this->object->getPosition().getX();
    this->center.y = (int)this->object->getPosition().getY();
    return this->center;
}

const SDL_Rect & Sprite::getVerticesPositions() {
    calculateVerticesPositions();
    return this->verticesPositions;
}

double Sprite::getAngle() const {
    return this->object->getRotation();
}

void Sprite::calculateVerticesPositions() {
    this->getCenter();
    this->verticesPositions.x = this->center.x - this->object->getSizeX()/2;
    this->verticesPositions.y = this->center.y - this->object->getSizeY()/2;
    this->verticesPositions.w = this->object->getSizeX();
    this->verticesPositions.h = this->object->getSizeY();
}
