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

Game::Game(Settings *settings) : settings(settings) {
    this->player = new Player();
    this->map = new Map(player, settings->getMapNumber());
}

Player *Game::getPlayer() const {
    return player;
}

Map *Game::getMap() const {
    return map;
}


