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
    ImageElement(const char *resourceFilePath, const SDL_Rect &verticesPosition, double angel = 0);
    SDL_Surface *getSurface() const;

    virtual const SDL_Point &getCenter();
    virtual const SDL_Rect &getVerticesPosition();
    virtual double getAngel() const;

protected:
    void calculateCenter();
    SDL_Surface *surface;
    SDL_Rect verticesPosition;
    SDL_Point center;
private:
    double angel;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_IMAGEELEMENT_H
