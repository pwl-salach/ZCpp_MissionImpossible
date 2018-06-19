//
// Created by salach on 3/2/18.
//
/*!
 * @file Obstacle.h
 * @brief Deklaracja klasy Obstacle
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_OBSTACLE_H
#define ZCPP_MISSIONIMPOSSIBLE_OBSTACLE_H

#include "PhysicalObject.h"
#include "Player.h"

/*!
 * @brief Abstrakcyjna klasa reprezentująca przeszkodę
 */
class Obstacle : virtual public PhysicalObject {
public:
    /*!
     * @brief Enum określający co blokuje dana przeszkoda
     */
    enum Blocking {
        VIEW = 1,        /*!< blokowany widok */
        MOVEMENT = 2,    /*!< blokowany ruch*/
        BOTH = 3         /*!< zarówno widok jak i ruch są blokowane*/
    };

    /*!
     * @brief Domyślny konstruktor
     */
    Obstacle() = default;

    /*!
     * @brief Wykorzystywany konstruktor.
     * @param pPosition pozycja centralnego punktu obiektu w środowisku
     * @param pSizeX rozwiar wzdłuż osi X
     * @param pSizeY rozwiar wzdłuż osi Y
     * @param pRotation rotacja w przestrzeni
     */
    Obstacle(Point pPosition, uint16_t pSizeX, uint16_t pSizeY, uint16_t pRotation);

    /*!
     * @return zwraca prawdę jeżeli przeszkoda blokuje ruch
     */
    bool blockingMovement();

    /*!
     * @return zwraca prawdę jeżeli przeszkoda blokuje widoczność
     */
    bool blockingView();


protected:
    Blocking blocks; /*!< określa co blokuje przeszkoda */
};


#endif //ZCPP_MISSIONIMPOSSIBLE_OBSTACLE_H
