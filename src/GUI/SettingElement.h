//
// Created by salach on 2/28/18.
//
/*!
 * @file SettingElement.h
 * @brief Deklaracja i definicja szablonu klasy SettingElement
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_SETTINGELEMENT_H
#define ZCPP_MISSIONIMPOSSIBLE_SETTINGELEMENT_H

#include "MenuElement.h"
#include "../Utils/Dictionary.h"

/*!
 * @brief Elementy tej klasy reprezentują wpisy w menu ustawień. Pozwalają na manipulację ich wartościami i ich prezentację.
 * @tparam T typ przypisanego parametru
 */
template<typename T> class SettingElement : public MenuElement {
public:
    /*!
     * @brief Wykorzystywamy konstruktor, inicjalizuje pola klasy
     * @param id pozycja obiektu w menu
     * @param text wyświetlany tekst
     * @param verticesPosition pozycje wierzchołków jako obiekt SDL_Rect
     * @param setting zarządzana opcja
     */
    SettingElement(uint8_t id, const std::string &text, const SDL_Rect &verticesPosition, T setting)
            : MenuElement(id, text, verticesPosition), setting(setting) {
        backedUpValue = setting;
    }

    /*!
     * @return nazwa opcji
     */
    const std::string getText() const override {
        return text + ": " + getSettingText();
    }

    /*!
     * @return wartość opcji przedstawiona jako tekst
     */
    const std::string getSettingText() const {
        if (std::is_same<T, bool>::value) {
            return setting ? Dictionary::YES : Dictionary::NO;
        }
        return std::to_string(setting);
    }

    /*!
     * @return wartość opcji
     */
    T getSetting() const {
        return setting;
    }

    /*!
     * @brief Zwiększa wartość zarządzanej opcji jeżeli jest mniejsza niż podana wartość graniczna
     * @param limit maksymalna wartość dla danej opcji
     */
    void increaseSettingValue(T limit) {
        if (std::is_same<T, bool>::value) {
            setting = true;
            return;
        }
        if (setting < limit) {
            setting = setting + 1;
        }
    }

    /*!
     * @brief Zmniejsza wartość zarządzanej opcji jeżeli jest większa niż podana wartość graniczna
     * @param limit minimalna wartość dla danej opcji
     */
    void decreaseSettingValue(T limit) {
        if (std::is_same<T, bool>::value) {
            setting = false;
            return;
        }
        if (setting > limit) {
            setting = setting - 1;
        }
    }

    /*!
     * @brief Zapisuje aktualną wartość
     */
    void saveChanges() {
        backedUpValue = setting;
    }

    /*!
     * Przywraca poprzednio zatwierdzoną wartość
     */
    void resetValue() {
        setting = backedUpValue;
    }

private:
    T setting;
    T backedUpValue;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_SETTINGELEMENT_H
