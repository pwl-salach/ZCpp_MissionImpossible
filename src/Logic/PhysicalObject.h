//
// Created by salach on 3/1/18.
//

/*!
 * @file PhysicalObject.h
 * @brief Deklaracja klasy PhysicalObject
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_PHYSICALOBJECT_H
#define ZCPP_MISSIONIMPOSSIBLE_PHYSICALOBJECT_H


#include <cstdint>
#include <map>
#include <vector>
#include "Point.h"

/*!
 * @brief Abstrakcyjna klasa reprezentująca obiekty fizyczne w grze
 */
class PhysicalObject {
public:
    /*!
     * @brief Ustawia inicjalną pozycję obiektu. Zwróci wyjątek jeżeli jeżeli wywoła się ją na już rozlokowanym obiekcie.
     * @param pPosition pozycja centralnego punku obiektu
     * @param pRotation rotacja obiektu
     */
    void setInitialOrientation(const Point &pPosition, uint16_t pRotation);

    /*!
     * @brief Oblicza współrzędne wierzchołków obiektu przesuniętego do innego położenia
     * @param pos sprawdzana pozycja
     * @param rot sprawdzany kąt
     * @return obliczone punkty wierzchołków
     */
    std::vector<Point> getCustomVerticesPosition(Point pos, uint16_t rot);

    /*!
     * @return obliczona wartość długości przekątnej
     */
    uint16_t getDiagonalLength();

    /*!
     * @return współrzędne wierzchołków obiektu, przez referencję
     */
    std::vector<Point> &getVerticesPosition();

    virtual ~PhysicalObject() = 0;

    /*!
     * @return pozycję obiektu
     */
    const Point &getPosition() const;

    /*!
     * @return rotację obiektu
     */
    uint16_t getRotation() const;

    /*!
     * @return wartość pola sizeX
     */
    uint16_t getSizeX() const;

    /*!
     * @return wartość pola sizeY
     */
    uint16_t getSizeY() const;

    /*!
     * @return nazwę pliku z teksturą obiektu
     */
    const std::string &getImageName() const;

protected:
    /*!
     * @brief Oblicza współrzędne wierzchołków obiektu w jego aktualnym położeniu
     * @return obliczone punkty wierzchołków zwrócone przez referencję
     */
    void calculateVerticesPosition();

    Point position;        /*!< pozycja*/
    uint16_t sizeX;        /*!< rozmiar wzdłuż osi x i 0 rotacji*/
    uint16_t sizeY;        /*!< rozmiar wzdłuż osi y i 0 rotacji*/
    uint16_t rotation;     /*!< rotacja */
    std::vector<Point> vertices;    /*!< położenie wierzchołków*/
    std::string imageName;      /*!< nazwa pliku z teksturą obiektu*/
};


#endif //ZCPP_MISSIONIMPOSSIBLE_PHYSICALOBJECT_H
