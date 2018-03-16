//
// Created by salach on 3/1/18.
//

#include "GameWindow.h"
#include "../Logic/Box.h"
#include "../Logic/Lake.h"

GameWindow::GameWindow(Game *pGame):game(pGame) {
    this->resolutionX = this->game->getMap().getSizeX();
    this->resolutionY = this->game->getMap().getSizeY();
    this->frameRate = 60;
    this->preparePauseMenuElements();
    this->prepareSprites();
    this->game->start();
    this->show();
}

void GameWindow::preparePauseMenuElements() {
    auto topMargin = uint16_t(this->resolutionY / 2);
    auto bottomMargin = uint16_t(this->resolutionY / 8);
    std::map<uint8_t, std::string> elementsBasicData {
            {PauseButtons::RESUME_GAME, Dictionary::RESUME_GAME},
            {PauseButtons::RESTART_LEVEL, Dictionary::RESTART_LEVEL},
            {PauseButtons::MAIN_MENU, Dictionary::MAIN_MENU},
            {PauseButtons::QUIT, Dictionary::QUIT}
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
    this->loop();
}

void GameWindow::loop() {
    Uint32  frameBeginning = 0;
    Uint32 frameEnd = 0;
    SDL_Event event{};
    while(this->visible) {
        frameBeginning = SDL_GetTicks();
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    this->game->quit();
                    this->visible = false;
                    break;
                case SDL_KEYDOWN:
                    handleKeyboardEvent(event);
                    break;
                default:
                    this->game->getPlayer().setMovement(Player::Movement::NONE);
                    this->game->getPlayer().setTurning(Player::Movement::NONE);
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
    if (this->game->getState() == Game::State::RUNNING) {
        auto key = event.key.keysym.sym;
        if(key == SDLK_UP){
            this->game->getPlayer().setMovement(Player::Movement::FORWARD);
        } else if (key == SDLK_DOWN){
            this->game->getPlayer().setMovement(Player::Movement::BACK);
        }

        if(key == SDLK_LEFT){
            this->game->getPlayer().setTurning(Player::Movement::TURN_LEFT);
        } else if (key == SDLK_RIGHT){
            this->game->getPlayer().setTurning(Player::Movement::TURN_RIGHT);
        }

//        switch (event.key.keysym.sym) {
//            case SDLK_UP:
//                this->game->getPlayer().setMovement(Player::Movement::FORWARD);
//                break;
//            case SDLK_DOWN:
//                this->game->getPlayer().setMovement(Player::Movement::BACK);
//                break;
//            case SDLK_LEFT:
//                this->game->getPlayer().setTurning(Player::Movement::TURN_LEFT);
//                break;
//            case SDLK_RIGHT:
//                this->game->getPlayer().setTurning(Player::Movement::TURN_RIGHT);
//                break;
//            case SDLK_RETURN:
//                break;
//            default:
//                break;
//        }
    }
}

void GameWindow::renderFrame() {
    switch (this->game->getState()){
        case Game::State::RUNNING:
            SDL_SetRenderDrawColor(this->renderer, 50, 160, 60, 200);
            for(auto sprite : this->sprites){
                SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface( renderer, sprite->getSurface());
                SDL_RenderCopyEx(this->renderer, spriteTexture, NULL, &sprite->getVerticesPositions(), sprite->getAngle(), NULL,
                                 SDL_FLIP_NONE);
                SDL_DestroyTexture(spriteTexture);
            }
            break;
        case Game::State::PAUSE:
            break;
    }
}

void GameWindow::prepareSprites() {
    this->sprites.push_back(new Sprite(&this->game->getPlayer(), "player.png"));
    for(auto object : this->game->getMap().getObstacles()){
        if(dynamic_cast<Box*>(object) != nullptr){
            this->sprites.push_back(new Sprite(object, "box.png"));
        } else if (dynamic_cast<Lake*>(object)) {
            this->sprites.push_back(new Sprite(object, "lake.png"));
        }
    }
}

void GameWindow::displayPauseManu() {

}

void GameWindow::chooseOption() {

}
