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
        PAUSE = 1
    };

    explicit Game(Settings *settings);
    void start();
    void loop();
    void update();
    void pause();
    void quit();

    Player &getPlayer();
    Map &getMap();
    Headquarters getHeadquarters() const;
    std::vector<Agent *>getAgents() const;

    State getState() const;

private:
    Player player;
    Settings *settings;
    Map map;
    Headquarters headquarters;
    std::vector<Agent*>agents;
    State state;
    std::thread updateLoop;
    uint8_t updatesPerSecond;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_GAME_H
