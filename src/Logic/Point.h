//
// Created by Salach on 03.03.2018.
//
/*!
 * @file Point.h
 * @brief Deklaracja klasy Point
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_POINT_H
#define ZCPP_MISSIONIMPOSSIBLE_POINT_H


#include <cstdint>

/*!
 * @brief Obiekty tej klasy reprezentują wszystkie pola opisane przez współrzędne x, y
 */
class Point {
public:
    /*!
     * @brief Domyślny konstruktor zwracający obiekt o nieustaloynch współrzędnych.
     */
    Point();

    /*!
     * @brief Kontruktor tworzący poprawnie zainicjowane punkty
     * @param x współrzędna X
     * @param y współrzędna Y
     */
    Point(float x, float y);

    /*!
     * @brief Operator porównujący dwa punkty
     * @param other inny obiekt tej klasy przekazany przez referencję
     * @return prawdę jeżeli współrzędne X i Y obu punktów są wystarczająco zbliżone do siebie
     */
    bool operator==(const Point &other) const;

    /*!
     * @param other inny obiekt tej klasy przekazany przez referencję
     * @return  prawdę jeżeli współrzędne X obu punktów są wystarczająco zbliżone do siebie
     */
    bool sameXCoordinate(const Point &other) const;

    /*!
     * @param other inny obiekt tej klasy przekazany przez referencję
     * @return  prawdę jeżeli współrzędne Y obu punktów są wystarczająco zbliżone do siebie
     */
    bool sameYCoordinate(const Point &other) const;

    /*!
     * @return współrzędną X
     */
    float getX() const;

    /*!
     * @return współrzędną Y
     */
    float getY() const;

    /*!
     * @return czy punkt został poprawnie zainicjowany
     */
    bool isSet() const;

private:
    float x;
    float y;
    bool set;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_POINT_H
