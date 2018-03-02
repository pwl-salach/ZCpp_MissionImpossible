//
// Created by salach on 3/2/18.
//

#include "Sprite.h"
#include "../Utils/FileManager.h"

Sprite::Sprite(PhysicalObject *pObject, std::string fileName) {
    this->object = pObject;
    this->surface = FileManager::loadImage(fileName);
}

const SDL_Point & Sprite::getCenter(){
    this->center.x = this->object->getPositionX();
    this->center.y = this->object->getPositionY();
    return center;
}

const SDL_Rect & Sprite::getVerticesPosition() {
    calculateVerticesPosition();
    return this->verticesPosition;
}

double Sprite::getAngel() const {
    return this->object->getRotation();
}

void Sprite::calculateVerticesPosition() {
    this->verticesPosition.x = this->object->getPositionX() - this->object->getSizeX()/2;
    this->verticesPosition.y = this->object->getPositionY() - this->object->getSizeY()/2;
    this->verticesPosition.w = this->object->getSizeX();
    this->verticesPosition.h = this->object->getSizeY();
}
