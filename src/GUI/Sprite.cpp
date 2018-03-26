//
// Created by salach on 3/2/18.
//

#include "Sprite.h"
#include "../Utils/FileManager.h"

Sprite::Sprite(PhysicalObject *pObject) {
    object = pObject;
    surface = FileManager::loadImage(object->getImageName());
}

const SDL_Point & Sprite::getCenter(){
    center.x = (int)object->getPosition().getX();
    center.y = (int)object->getPosition().getY();
    return center;
}

const SDL_Rect & Sprite::getVerticesPositions() {
    calculateVerticesPositions();
    return verticesPositions;
}

double Sprite::getAngle() const {
    return object->getRotation();
}

void Sprite::calculateVerticesPositions() {
    getCenter();
    verticesPositions.x = center.x - object->getSizeX()/2;
    verticesPositions.y = center.y - object->getSizeY()/2;
    verticesPositions.w = object->getSizeX();
    verticesPositions.h = object->getSizeY();
}
