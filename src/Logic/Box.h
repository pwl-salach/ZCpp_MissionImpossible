//
// Created by salach on 3/1/18.
//
/*!
 * @file Box.h
 * @brief Deklaracja klasy Box
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_BOX_H
#define ZCPP_MISSIONIMPOSSIBLE_BOX_H

#include "Obstacle.h"
#include "Player.h"
#include "Point.h"

/*!
 * @brief Obiekty tej klasy reprezentują przeszkody blokujące zarówno widoczność jak i przejście.
 */
class Box: public Obstacle{
public:
    /*!
     * @brief Wykorzystywany konstruktor.
     * @param pPosition pozycja centralnego punktu obiektu w środowisku
     * @param pSizeX rozwiar wzdłuż osi X
     * @param pSizeY rozwiar wzdłuż osi Y
     * @param pRotation rotacja w przestrzeni
     */
    Box(Point pPosition, uint16_t pSizeX, uint16_t pSizeY, uint16_t pRotation);

};


#endif //ZCPP_MISSIONIMPOSSIBLE_BOX_H
