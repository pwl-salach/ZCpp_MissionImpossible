//
// Created by salach on 3/2/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_SPRITE_H
#define ZCPP_MISSIONIMPOSSIBLE_SPRITE_H


#include <SDL2/SDL_surface.h>
#include "../Logic/PhysicalObject.h"
#include "ImageElement.h"

class Sprite : public ImageElement{
public:
    Sprite(PhysicalObject *pObject, std::string fileName);

    const SDL_Point & getCenter() override;

    const SDL_Rect & getVerticesPosition() override;

    double getAngel() const override;

private:
    void calculateVerticesPosition();
    PhysicalObject *object;

};


#endif //ZCPP_MISSIONIMPOSSIBLE_SPRITE_H
