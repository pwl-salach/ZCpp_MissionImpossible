//
// Created by Salach on 20.02.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_IMAGEELEMENT_H
#define ZCPP_MISSIONIMPOSSIBLE_IMAGEELEMENT_H


#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

class ImageElement {
public:
    ImageElement();

    ImageElement(const char *fileName, const SDL_Rect &verticesPositions, float angle = 0);

    SDL_Surface *getSurface() const;

    virtual const SDL_Point &getCenter();

    virtual const SDL_Rect &getVerticesPositions();

    virtual float getAngle() const;

protected:
    void calculateCenter();

    SDL_Surface *surface;
    SDL_Rect verticesPositions;
    SDL_Point center;

private:
    float angle;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_IMAGEELEMENT_H
