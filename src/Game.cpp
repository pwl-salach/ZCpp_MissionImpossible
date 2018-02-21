//
// Created by Salach on 19.02.2018.
//

#include "Game.h"

Game::Game() {

}

Game::~Game() {
    SDL_Quit();
}

void Game::quit() {

}

void Game::start() {
    startWindow->disappear();
}


