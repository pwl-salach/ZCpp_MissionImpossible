//
// Created by Salach on 21.03.2018.
//
/*!
 * @file Fence.h
 * @brief Deklaracja klasy Fence
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_FENCE_H
#define ZCPP_MISSIONIMPOSSIBLE_FENCE_H


#include "Obstacle.h"

/*!
 * @brief Obiekty tej klasy wyznaczają obwód mapy
 */
class Fence: public Obstacle {
public:
    /*!
     * @brief Wykorzystywany konstruktor.
     * @param pPosition pozycja centralnego punktu obiektu w środowisku
     * @param pSizeX rozmiar wzdłuż osi X
     * @param pRotation rotacja w przestrzeni
     */
    Fence(Point pPosition, uint16_t pSizeX, uint16_t pRotation);

};

#endif //ZCPP_MISSIONIMPOSSIBLE_FENCE_H
