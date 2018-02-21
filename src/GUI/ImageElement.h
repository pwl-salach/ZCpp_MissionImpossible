//
// Created by Salach on 20.02.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_IMAGEELEMENT_H
#define ZCPP_MISSIONIMPOSSIBLE_IMAGEELEMENT_H


#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

class ImageElement {
public:
    ImageElement(const char *resourceFilePath, const SDL_Rect &verticesPosition, double angel = 0);
private:
    void calculateCenter();
    SDL_Rect verticesPosition;
    SDL_Surface *surface;
public:
    void move();
    void rotate();
    const SDL_Rect &getverticesPosition() const;
    SDL_Surface *getSurface() const;
    const SDL_Point &getCenter() const;
    double getAngel() const;

private:
    SDL_Point center;
    double angel;

};


#endif //ZCPP_MISSIONIMPOSSIBLE_IMAGEELEMENT_H
