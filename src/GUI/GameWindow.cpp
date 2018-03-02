//
// Created by salach on 3/1/18.
//

#include "GameWindow.h"
#include "../Logic/Box.h"
#include "../Logic/Lake.h"

GameWindow::GameWindow(Game *pGame):game(pGame) {
    this->resolutionX = this->game->getMap()->getSizeX();
    this->resolutionY = this->game->getMap()->getSizeY();
    this->frameRate = 25;
    this->preparePauseMenuElements();
    this->prepareSprites();
    this->show();
}

void GameWindow::preparePauseMenuElements() {
    uint16_t topMargin = uint16_t(this->resolutionY / 2);
    uint16_t bottomMargin = uint16_t(this->resolutionY / 8);
    std::map<uint8_t, std::string> elementsBasicData {
            {MenuButtons::RESUME_GAME, Dictionary::RESUME_GAME},
            {MenuButtons::RESTART_LEVEL, Dictionary::RESTART_LEVEL},
            {MenuButtons::MAIN_MENU, Dictionary::MAIN_MENU},
            {MenuButtons::QUIT, Dictionary::QUIT}
    };
    std::vector<SDL_Rect> menuElementsPositions = this->calculateMenuElementsCoordinates(elementsBasicData, topMargin, bottomMargin);
    uint8_t i = 0;
    for (auto &pair : elementsBasicData) {
        this->pauseMenuElements.push_back(
                new MenuElement(pair.first, pair.second, menuElementsPositions.at(i)));
        i++;
    }

}

void GameWindow::show() {
    this->window= SDL_CreateWindow(
            "Mission Impossible!!!",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            this->resolutionX,
            this->resolutionY,
            SDL_WINDOW_OPENGL);
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    this->visible = true;
    this->state = State::RUNNING;
    this->loop();
}

void GameWindow::loop() {
    Uint32  frameBeginning = 0;
    Uint32 frameEnd = 0;
    SDL_Event event;
    while(this->visible) {
        frameBeginning = SDL_GetTicks();
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    this->visible = false;
                    break;
                case SDL_KEYDOWN:
                    handleKeyboardEvent(event);
                    break;
                default:
                    break;
            }
        }
        SDL_RenderClear(renderer);
        renderFrame();
        SDL_RenderPresent(renderer);
        frameEnd = SDL_GetTicks();
        enforceFrameRate(frameBeginning, frameEnd);
    }
}

void GameWindow::disappear() {

}

void GameWindow::handleKeyboardEvent(SDL_Event &event) {

}

void GameWindow::renderFrame() {
    switch (this->state){
        case State::RUNNING:
            SDL_SetRenderDrawColor(this->renderer, 50, 160, 60, 200);
            for(auto sprite : this->sprites){
                SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface( renderer, sprite->getSurface());
                SDL_RenderCopyEx(this->renderer, spriteTexture, NULL, &sprite->getVerticesPosition(), sprite->getAngel(), NULL,
                                 SDL_FLIP_NONE);
            }
            break;
        case State::PAUSE:
            break;
    }
}

void GameWindow::prepareSprites() {
    this->sprites.push_back(new Sprite(this->game->getPlayer(), "player.png"));
    for(auto object : this->game->getMap()->getObstacles()){
        if(dynamic_cast<Box*>(object) != nullptr){
            this->sprites.push_back(new Sprite(object, "box.png"));
        } else if (dynamic_cast<Lake*>(object)) {
            this->sprites.push_back(new Sprite(object, "lake.png"));
        }
    }
}
