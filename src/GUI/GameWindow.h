//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_GAMEWINDOW_H
#define ZCPP_MISSIONIMPOSSIBLE_GAMEWINDOW_H


#include "../Logic/Game.h"
#include "Sprite.h"

class GameWindow : public Window {

public:
    GameWindow(Game *pGame, StartWindow *startWindow);

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
