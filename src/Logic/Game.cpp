//
// Created by Salach on 19.02.2018.
//

#include "Game.h"


void Game::start() {
    this->state = State::RUNNING;
    this->updateLoop = std::thread(&Game::loop, this);
}

void Game::quit() {
    this->pause();
}

void Game::pause() {
    this->state = State::PAUSE;
    updateLoop.join();
}

Game::Game(Settings *settings) : settings(settings){
    this->updatesPerSecond = 30;
}

Player &Game::getPlayer() {
    return player;
}

Map &Game::getMap(){
    return map;
}

Headquarters Game::getHeadquarters() const {
    return headquarters;
}

std::vector<Agent *> Game::getAgents() const {
    return agents;
}

Game::State Game::getState() const {
    return state;
}

void Game::loop() {
    while(this->state == State::RUNNING) {
        auto begin = std::chrono::high_resolution_clock::now();
        this->update();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        auto stepDuration = std::chrono::milliseconds(1000/this->updatesPerSecond);
        std::this_thread::sleep_for(stepDuration - duration);
        //std::chrono::duration<std::chrono::nanoseconds> ddd = end - begin;
        //std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << "ns";
    }
}

void Game::update() {
    if(!this->map.checkCollisions(&player)) {
        this->player.move();
        bool victory = this->map.checkVictoryCondition();
        if(victory){
            this->state = State::VICTORY;
        }
    }
}
