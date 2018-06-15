//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_GAMEWINDOW_H
#define ZCPP_MISSIONIMPOSSIBLE_GAMEWINDOW_H


#include "../Logic/Game.h"
#include "Sprite.h"

class GameWindow : public Window{

public:
    GameWindow(Game *pGame);

    void show() override;

    void disappear() override;

private:
    enum PauseButtons{
        RESUME_GAME = 0,
        RESTART_LEVEL = 1,
        MAIN_MENU = 2,
        QUIT = 3
    };
    void loop() override;
    void handleKeyboardEvent(SDL_Event &event) override;
    void renderFrame() override;
    void preparePauseMenuElements();
    void prepareSprites();
    void renderGameScreen();
    void displayVictoryScreen();
    void displayLoseScreen();
    void displayPauseManu();
    void chooseOption();
    void moveCursorUp();
    void moveCursorDown();
    void restartLevel();
    void goBackToMaunManu();
    void resumeGame();
    void quit();

    Game *game;
    std::vector<MenuElement*> pauseMenuElements;
    std::vector<Sprite*> sprites;
    uint8_t selectedElementIndex;
    ImageElement grass;
    SDL_Texture *grassTexture;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_GAMEWINDOW_H
