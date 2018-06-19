//
// Created by Salach on 25.03.2018.
//

/*!
 * @file Line.h
 * @brief Deklaracja klasy Line
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_LINE_H
#define ZCPP_MISSIONIMPOSSIBLE_LINE_H


#include "Point.h"

/*!
 * @brief Klasa użyteczna przy części obliczeń związanych z rozłozeniem obiektów w przestrzeni
 */
class Line {
public:
    /*!
     * @brief Domyślny konstruktor
     */
    Line() = default;

    /*!
     * @brief Wykorzystywany konstruktor. Wyznacza współczynniki prostej przechodzącej przez dwa punkty
     * @param first pierwszy z punktów
     * @param second drugi z punktów
     */
    Line(Point &first, Point &second);

    /*!
     * @brief Oblicza wartość funkcji dla wskazanego x
     * @param x wartość współrzędnej x
     * @return współrzędna y
     */
    float calculate(float x);

protected:
    /*!
     * @brief Oblicza współczynnika a prostej i ustawia wartość pola chronionego
     * @param first pierwszy z punktów
     * @param second drugi z punktów
     */
    void calculateFactorA(const Point &first, const Point &second);

    /*!
     * @brief Oblicza współczynnika b prostej i ustawia wartość pola chronionego
     * @param first pierwszy z punktów
     * @param second drugi z punktów
     */
    void calculateFactorB(const Point &first, const Point &second);

    float a;    /*!< współczynnik a w równaniu prostej*/
    float b;    /*!< współczynnik b w równaniu prostej*/
};


#endif //ZCPP_MISSIONIMPOSSIBLE_LINE_H
