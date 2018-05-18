//
// Created by Salach on 20.02.2018.
//

#include <SDL2/SDL_image.h>
#include "ImageElement.h"
#include "../Utils/FileManager.h"

ImageElement::ImageElement(const char *fileName, const SDL_Rect &verticesPositions, float angle)
        : verticesPositions(verticesPositions), angle(angle) {
    surface = FileManager::loadImage(fileName);
    calculateCenter();
}

void ImageElement::calculateCenter() {
    center.x = verticesPositions.x + verticesPositions.w/2;
    center.y = verticesPositions.y + verticesPositions.h/2;
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

float ImageElement::getAngle() const {
    return angle;
}

ImageElement::ImageElement() {}


