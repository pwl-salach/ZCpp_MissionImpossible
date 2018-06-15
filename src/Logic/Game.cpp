//
// Created by Salach on 19.02.2018.
//

#include "Game.h"

#include <utility>


void Game::start() {
    state = State::RUNNING;
    updateLoop = std::thread(&Game::loop, this);
    headquarters.planSearching();
}

void Game::quit() {
    pause();
    for(auto agent : agents){
        delete agent;
    }
    agents.clear();
}

void Game::pause() {
    state = State::PAUSE;
    updateLoop.join();
}

Game::Game(Settings *pSettings, std::vector<Agent *> pAgents) : settings(pSettings),
                                                                agents(std::move(pAgents)),
                                                                headquarters(Headquarters(&agents, &environment)),
                                                                environment(Environment(&player, &agents, settings->getEnvironmentNumber())){
    updatesPerSecond = 25;
}

Player &Game::getPlayer() {
    return player;
}

Environment &Game::getEnvironment(){
    return environment;
}

Game::State Game::getState() const {
    return state;
}

void Game::loop() {
    while(state == State::RUNNING) {
        auto begin = std::chrono::high_resolution_clock::now();
        update();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        auto stepDuration = std::chrono::milliseconds(1000/updatesPerSecond);
        std::this_thread::sleep_for(stepDuration - duration);
    }
}

void Game::update() {
    if(!environment.checkCollisions(&player)) {
        player.move();
        bool victory = environment.checkVictoryCondition();
        if(victory){
            state = State::VICTORY;
        }
    }
    for(auto agent : agents){
        agent->lookAround(&environment);
        agent->update();
        auto obstacle = environment.checkCollisions(agent);
        if(obstacle == nullptr){
            agent->move();
        } else {
            agent->moveAwayFrom(obstacle);
        }
        if(agent->catchPlayer(&player)){
            state = State::LOSE;
        }
    }
    headquarters.planSearching();
}

Settings *Game::getSettings() const {
    return settings;
}

const std::vector<Agent *> &Game::getAgents() const {
    return agents;
}
