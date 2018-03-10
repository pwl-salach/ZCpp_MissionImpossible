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
    Sprite(PhysicalObject *pObject, const std::string &fileName);

    const SDL_Point & getCenter() override;

    const SDL_Rect & getVerticesPositions() override;

    double getAngle() const override;

private:
    void calculateVerticesPositions();
    PhysicalObject *object;

};


#endif //ZCPP_MISSIONIMPOSSIBLE_SPRITE_H
