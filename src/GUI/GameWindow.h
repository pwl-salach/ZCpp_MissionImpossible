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

protected:
    void loop() override;

    void handleKeyboardEvent(SDL_Event &event) override;

    void renderFrame() override;

private:
    enum MenuButtons{
        RESUME_GAME = 0,
        RESTART_LEVEL = 1,
        MAIN_MENU = 2,
        QUIT= 3
    };
    enum State{
        RUNNING = 0,
        PAUSE = 1
    };
    void preparePauseMenuElements();
    void prepareSprites();

    Game *game;
    std::vector<MenuElement*> pauseMenuElements;
    std::vector<Sprite*> sprites;
    State state;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_GAMEWINDOW_H
