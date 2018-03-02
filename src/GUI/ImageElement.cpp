//
// Created by Salach on 20.02.2018.
//

#include <SDL2/SDL_image.h>
#include "ImageElement.h"
#include "../Utils/FileManager.h"

ImageElement::ImageElement(const char *resourceFilePath, const SDL_Rect &verticesPosition, double angel)
        : verticesPosition(verticesPosition), angel(angel) {
    this->surface = FileManager::loadImage(resourceFilePath);
    this->calculateCenter();
}

void ImageElement::calculateCenter() {
    this->center.x = verticesPosition.x + verticesPosition.w/2;
    this->center.y = verticesPosition.y + verticesPosition.h/2;
}

const SDL_Rect & ImageElement::getVerticesPosition() {
    return verticesPosition;
}

SDL_Surface *ImageElement::getSurface() const {
    return surface;
}

const SDL_Point & ImageElement::getCenter() {
    return center;
}

double ImageElement::getAngel() const {
    return angel;
}

ImageElement::ImageElement() {}


