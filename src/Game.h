//
// Created by Salach on 19.02.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_GAME_H
#define ZCPP_MISSIONIMPOSSIBLE_GAME_H

#include "GUI/StartWindow.h"

class Game {

public:
    Game();
    virtual ~Game();
    void start();
    void quit();
private:
    StartWindow *startWindow;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_GAME_H
