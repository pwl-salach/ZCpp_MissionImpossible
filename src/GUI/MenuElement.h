//
// Created by Salach on 20.02.2018.
//
/*!
 * @file MenuElement.h
 * @brief Deklaracja klasy MenuElement
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_MANUELEMENT_H
#define ZCPP_MISSIONIMPOSSIBLE_MANUELEMENT_H

#include "ImageElement.h"
#include <string>

/*!
 * @brief Obiekty tej klasy reprezentują wiersze w opcjach dające możliwość jedynie ich zatwierdzenia.
 */
class MenuElement {
public:
    /*!
     * @brief Wykorzystywamy konstruktor, inicjalizuje pola klasy
     * @param id pozycja obiektu w menu
     * @param text wyświetlany tekst
     * @param verticesPosition pozycje wierzchołków jako obiekt SDL_Rect
     */
    MenuElement(uint8_t id, const std::string &text, const SDL_Rect &verticesPosition);

    virtual ~MenuElement();

    /*!
     * @return zwraca pozycję obiektu w menu
     */
    uint8_t getId() const;

    /*!
     * @return czy jest aktualnie wybrany
     */
    bool isSelected() const;

    /*!
     * @return tekst opcji
     */
    virtual const std::string getText() const;

    /*!
     * @return referencję do obiektu SDL_Rect reprezentującego rozmieszczenie wierzchołków
     */
    const SDL_Rect &getVerticesPositions() const;

    /*!
     * @brief Ustawia wartość pola selected na podaną w argumencie
     * @param pSelected nowa wartość pola selected
     */
    void setSelected(bool pSelected);

protected:
    std::string text;
    SDL_Rect verticesPositions;
    bool selected;
    uint8_t id;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_MANUELEMENT_H
