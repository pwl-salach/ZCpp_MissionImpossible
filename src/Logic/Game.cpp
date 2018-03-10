//
// Created by Salach on 19.02.2018.
//

#include "Game.h"


void Game::quit() {
    updateLoop.join();
}

void Game::start() {

}

Game::Game(Settings *settings) : settings(settings){
    this->state = State::RUNNING;
    this->map = Map(&player, settings->getMapNumber());
    this->updateLoop = std::thread(&Game::loop, this);
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
    auto begin = std::chrono::high_resolution_clock::now();
    if (this->state == State::RUNNING){
        this->update();
    }
    auto end = std::chrono::high_resolution_clock::now();
    //std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << "ns";

}

void Game::update() {

}


