//
// Created by salach on 3/1/18.
//
/*!
 * @file GameWindow.h
 * @brief Deklaracja klasy GameWindow
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_GAMEWINDOW_H
#define ZCPP_MISSIONIMPOSSIBLE_GAMEWINDOW_H


#include "../Logic/Game.h"
#include "Sprite.h"

/*!
 * @brief Głowne okno gry, prezentuje przebieg rozgrywki i oddziaływuje z użytkownikiem.
 */
class GameWindow : public Window {
public:
    /*!
     * @brief Wykorzystywany konstruktor.
     * @param pGame wskaźnik do bobiektu gry
     * @param startWindow wskaźnik do okna startowego, dający możliwość powrotu do menu
     */
    GameWindow(Game *pGame, StartWindow *startWindow);

    /*!
     * @brief Nadpisana funkcjaz klasy bazowej
     * @see Window.h
     */
    void show() override;

private:
    enum PauseButtons {
        RESUME_GAME = 0,
        RESTART_LEVEL = 1,
        MAIN_MENU = 2,
        QUIT = 3
    };

    void loop() override;

    void handleKeyboardEvent(SDL_Event &event) override;

    void renderFrame() override;

    void prepareEndGameElements();

    void preparePauseMenuElements();

    void prepareMenuElements(std::map<uint8_t, std::string> elementsData, std::vector<MenuElement *> &container);

    void prepareSprites();

    void removeSprites();

    void renderGameScreen();

    void displayVictoryScreen();

    void displayLoseScreen();

    void displayPauseMenu();

    void displayEndGameMenu();

    void chooseOption();

    void restartLevel();

    void goBackToMainMenu();

    void resumeGame();

    Game *game;
    StartWindow *startWindow;
    std::vector<MenuElement *> pauseMenuElements;
    std::vector<MenuElement *> endGameElements;
    std::vector<Sprite *> sprites;
    ImageElement grass;
    SDL_Texture *grassTexture;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_GAMEWINDOW_H
