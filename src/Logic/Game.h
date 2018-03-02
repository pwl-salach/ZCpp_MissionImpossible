//
// Created by Salach on 19.02.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_GAME_H
#define ZCPP_MISSIONIMPOSSIBLE_GAME_H

#include "../GUI/StartWindow.h"
#include "Map.h"

class Game {

public:
    Game(Settings *settings);
    virtual ~Game();
    void start();
    void quit();

    Player *getPlayer() const;

    Map *getMap() const;

private:
    Player* player;
    Settings *settings;
    Map *map;

};


#endif //ZCPP_MISSIONIMPOSSIBLE_GAME_H
