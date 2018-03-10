//
// Created by Salach on 19.02.2018.
//

#include "Game.h"


Game::~Game() {
}

void Game::quit() {

}

void Game::start() {

}

Game::Game(Settings *settings) : settings(settings){
    this->state = State::RUNNING;
    this->map = Map(&player, settings->getMapNumber());
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


