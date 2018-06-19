//
// Created by Salach on 18.02.2018.
//

/*!
 * @file Window.h
 * @brief Deklaracja klasy Window
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_WINDOW_H
#define ZCPP_MISSIONIMPOSSIBLE_WINDOW_H

#include "SDL2/SDL.h"
#include "ImageElement.h"
#include "MenuElement.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>
#include <vector>

/*!
 * @brief Abstrakcyjna klasa okna
 */
class Window {
public:
    virtual ~Window();

    /*!
     * @brief Wykonuje ostatecnze tworzenie okna i jego prezentację
     */
    virtual void show() = 0;

    /*!
     * @brief Niszczy widoczne okno
     */
    void disappear();

protected:
    /*!
     * Wirtaulna metoda odpowiadająca za ciągłe wyświetlanie okna i interakcje z użytkownikiem
     */
    virtual void loop() = 0;

    /*!
     * @brief Wirtualna metoda odpowiedzialna za przetwarzanie przycików naciskanych przez użytkownika. Ich obsługa jest specyficzna dla każdego okna.
     * @param event wydarzenie związane interakcją użytkownika
     */
    virtual void handleKeyboardEvent(SDL_Event &event) = 0;

    /*!
     * @brief Metoda przygotowująca obraz do wyświetlenia. Specyficzna dla każdego okna, dlatego też jest wirtualna.
     */
    virtual void renderFrame()=0;

    /*!
     * @brief Metoda przygotowująca bibliotekę SDL do pracy
     */
    void initSDL();

    /*!
     * @brief Metoda kończąca pracę biblioteki SDL
     */
    void quitSDL();

    /*!
     * @brief Metoda zaznaczająca pierwszy element z aktualnie widocznego menu.
     */
    void selectFirstElement();

    /*!
     * @brief Przesuwa zaznaczenie na poprzednią (patrząc od góry do dołu) opcję
     */
    void moveCursorUp();

    /*!
     * @brief Przesuwa zaznaczenie na kolejną (patrząc od góry do dołu) opcję
     */
    void moveCursorDown();

    /*!
     * @brief Odznacza aktualnie wybrany element menu
     */
    void clearSelection();

    /*!
     * @brief Metoda wprowadzająca opóźnienie między kolejnymi renredowanymi klatkami, utrzymująca stałe odświeżanie.
     * @param frameBeginning czas rozpoczęcia przetwarzania logiki w oknie
     * @param frameActionsEnd czas zakończenia przetwarzania logiki w oknie
     */
    void enforceFrameRate(Uint32 frameBeginning, Uint32 frameActionsEnd);

    std::vector<SDL_Rect> calculateMenuElementsCoordinates(std::map<uint8_t, std::string> &elementsTexts,
                                                           uint16_t martinTop,
                                                           uint16_t marginBottom);
    /*!
     * @brief Wyznacza szerokość elementu menu na podstawie jego tekstu i oczekiwanej wysokości.
     * @param text tekst do wyświetlenia w danym elemencie
     * @param elementHeight wysokość elementu menu
     * @return szerokość elementu
     */
    uint16_t getElementWidth(std::string text, uint16_t elementHeight);

    SDL_Texture *logoTexture; /*!< telstura loga*/
    TTF_Font *font; /*!< domyślna czcionka tekstów w oknie*/
    std::vector<MenuElement *> *visibleElements; /*!< widoczne elementy menu*/
    SDL_Window *window; /*!< wskaźnik do obiektu okna typu SDL_Window*/
    SDL_Renderer *renderer; /*!< obiekt odpowiedzialny za renderowanie okna*/
    ImageElement logo;  /*!< obiekt odpowiadający logu*/
    bool visible; /*!< widoczność okna*/
    uint8_t frameRate; /*!< częstotliwość odświeżania*/
    uint16_t resolutionX; /*!< rozdzielczość X okna*/
    uint16_t resolutionY; /*!< rozdzielczość Y okna*/
    uint8_t selectedElementIndex; /*!< numer wybranego elementu menu*/
};


#endif //ZCPP_MISSIONIMPOSSIBLE_WINDOW_H
