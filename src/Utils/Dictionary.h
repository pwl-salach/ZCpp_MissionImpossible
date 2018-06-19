//
// Created by Salach on 21.02.2018.
//
/*!
 * @file Dictionary.h
 * @brief Deklaracja klasy Dictionary
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_DICTIONARY_H
#define ZCPP_MISSIONIMPOSSIBLE_DICTIONARY_H

#include <string>
#include <vector>

/*!
 * @brief Klasa zawiera stałe pola statyczne będące tekstami wykorzystywanymi w grze oraz metody statyczne manipulujące ciągami znaków.
 */
class Dictionary {
public:
    static const std::string START_GAME;
    static const std::string SETTINGS;
    static const std::string ENVIRONMENT_NUMBER;
    static const std::string NUMBER_OF_AGENTS;
    static const std::string RANGE_OF_VIEW;
    static const std::string ANGLE_OF_VIEW;
    static const std::string DEBUG;
    static const std::string ACCEPT;
    static const std::string CANCEL;
    static const std::string QUIT;
    static const std::string YES;
    static const std::string NO;
    static const std::string RESUME_GAME;
    static const std::string RESTART_LEVEL;
    static const std::string MAIN_MENU;

    /*!
     * @brief Dzieli podany ciąg znaków względem podanego znaku.
     * @param text manipulowany ciąg znaków
     * @param delimiter znak względem którego odbywa się rozbijanie stringa
     * @return wektor z kolejnymi elementami ciągu znaków
     */
    static std::vector<std::string> splitString(std::string text, char delimiter);

    /*!
     * @brief Wycina z ciągu znaków wskazany fragment
     * @param text manipulowany ciąg znaków przekazany przez referencję
     * @param partToBeCut fragment tekstu do usunięcia
     */
    static void cutString(std::string &text, const std::string &partToBeCut);

    /*!
     * @brief Sprawdza czy jeden ciąg znaków rozpoczyna się od innego wskazanego
     * @param text sprawdzany tekst
     * @param part sprawdzany fragmeny ciągu znaków
     * @return prawdę jeżli spełnione są wymagania
     */
    static bool stringStartsWith(const std::string &text, const std::string &part);
};

#endif //ZCPP_MISSIONIMPOSSIBLE_DICTIONARY_H
