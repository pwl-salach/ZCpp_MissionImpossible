//
// Created by salach on 3/1/18.
//

/*!
 * @file Lake.h
 * @brief Deklaracja klasy Lake
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_LAKE_H
#define ZCPP_MISSIONIMPOSSIBLE_LAKE_H

#include "Obstacle.h"
#include "Player.h"

/*!
 * @brief Obiekty tej klasy reprezentują przeszkody blokujące tylko przejście.
 */
class Lake : public Obstacle {
public:
    /*!
     * @brief Wykorzystywany konstruktor.
     * @param pPosition pozycja centralnego punktu obiektu w środowisku
     * @param pSizeX rozwiar wzdłuż osi X
     * @param pSizeY rozwiar wzdłuż osi Y
     * @param pRotation rotacja w przestrzeni
     */
    Lake(Point pPosition, uint16_t pSizeX, uint16_t pSizeY, uint16_t pRotation);
};


#endif //ZCPP_MISSIONIMPOSSIBLE_LAKE_H
