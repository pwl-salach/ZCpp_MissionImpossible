//
// Created by salach on 3/2/18.
//

/*!
 * @file Sprite.h
 * @brief Deklaracja klasy Sprite
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_SPRITE_H
#define ZCPP_MISSIONIMPOSSIBLE_SPRITE_H


#include <SDL2/SDL_surface.h>
#include "../Logic/PhysicalObject.h"
#include "ImageElement.h"

/*!
 * @brief Obiekty tej klasy są graficznymi reprezentacjami obiektów "fizycznych" występujących w grze
 */
class Sprite : public ImageElement {
public:
    /*!
     * @brief Wykorzystywany konstruktor
     * @param pObject
     */
    Sprite(PhysicalObject *pObject);

    /*!
     * @brief Nadpisana funkcjaz klasy bazowej
     * @see ImageElement.h
     */
    const SDL_Point &getCenter() override;

    /*!
     * @brief Nadpisana funkcjaz klasy bazowej
     * @see ImageElement.h
     */
    const SDL_Rect &getVerticesPositions() override;

    /*!
     * @brief Nadpisana funkcjaz klasy bazowej
     * @see ImageElement.h
     */
    float getAngle() const override;

private:
    void calculateVerticesPositions();

    PhysicalObject *object;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_SPRITE_H
