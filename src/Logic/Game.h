//
// Created by Salach on 19.02.2018.
//

/*!
 * file
 * \brief Declaration of the Game class
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_GAME_H
#define ZCPP_MISSIONIMPOSSIBLE_GAME_H

#include <thread>
#include "../GUI/StartWindow.h"
#include "Map.h"
#include "Headquarters.h"

/*!
 * \brief Main class containing basic rules
 */
class Game {

public:
    enum State{
        RUNNING = 0,
        PAUSE = 1,
        VICTORY = 3,
        LOSE = 4
    };

    Game(Settings *pSettings, std::vector<Agent *> pAgents);
    void start();
    void loop();
    void update();
    void pause();
    void quit();
    State getState() const;
    Player &getPlayer();
    Map &getMap();
    Settings *getSettings() const;
    const std::vector<Agent *> &getAgents() const;

private:
    State state;
    Player player;
    Settings *settings;
    std::vector<Agent*>agents;
    Map map;
    Headquarters headquarters;
    std::thread updateLoop;
    uint8_t updatesPerSecond;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_GAME_H
