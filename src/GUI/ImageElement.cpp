//
// Created by Salach on 20.02.2018.
//

#include <SDL2/SDL_image.h>
#include "ImageElement.h"
#include "../Utils/FileManager.h"

ImageElement::ImageElement(const char *fileName, const SDL_Rect &verticesPositions, double angel)
        : verticesPositions(verticesPositions), angle(angel) {
    this->surface = FileManager::loadImage(fileName);
    this->calculateCenter();
}

void ImageElement::calculateCenter() {
    this->center.x = verticesPositions.x + verticesPositions.w/2;
    this->center.y = verticesPositions.y + verticesPositions.h/2;
}

const SDL_Rect & ImageElement::getVerticesPositions() {
    return verticesPositions;
}

SDL_Surface *ImageElement::getSurface() const {
    return surface;
}

const SDL_Point & ImageElement::getCenter() {
    return center;
}

double ImageElement::getAngle() const {
    return angle;
}

ImageElement::ImageElement() {}


