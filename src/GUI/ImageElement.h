//
// Created by Salach on 20.02.2018.
//
/*!
 * @file ImageElement.h
 * @brief Deklaracja klasy ImageElement
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_IMAGEELEMENT_H
#define ZCPP_MISSIONIMPOSSIBLE_IMAGEELEMENT_H


#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

/*!
 * @brief Obiekty tej klasy reprezentują obrazy niebędące fizycznymi obiektami w grze, takie jak logo, tło.
 */
class ImageElement {
public:
    /*!
     * @brief Domyślny konstruktor
     */
    ImageElement();

    /*!
     * @brief Wykorzystywany konstruktor
     * @param fileName nazwa pliku z teksturą
     * @param verticesPositions  pozycje wierzchołków jako obiekt klasy SDL_Rect
     * @param angle kąt pod jakim umieszony jest obiekt na ekranie
     */
    ImageElement(const char *fileName, const SDL_Rect &verticesPositions, float angle = 0);

    /*!
     * @return wskaźnik do obiektu SDL_Surface reprezentującego obraz
     */
    SDL_Surface *getSurface() const;

    /*!
     * @return centralny punk jako referencja do obiektu SDL_Point
     */
    virtual const SDL_Point &getCenter();

    /*!
     * @return referencję do obiektu SDL_Rect reprezentującego rozmieszczenie wierzchołków obrazu
     */
    virtual const SDL_Rect &getVerticesPositions();

    /*!
     * @return rotacja obrazu
     */
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
