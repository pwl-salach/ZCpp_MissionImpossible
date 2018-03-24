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
    SDL_Rect logoPos {this->resolutionX/4, this->resolutionY/8, this->resolutionX/2, this->resolutionY/4};
    this->logo = ImageElement("logo.png", logoPos);
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

void GameWindow::prepareSprites() {
    for(Obstacle* object : this->game->getMap().getObstacles()){
        this->sprites.push_back(new Sprite(object));
    }
    this->sprites.push_back(new Sprite(&this->game->getPlayer()));
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
    this->logoTexture = SDL_CreateTextureFromSurface(this->renderer, this->logo.getSurface());
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
                case SDL_KEYUP:
                    handleKeyboardEvent(event);
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

void GameWindow::handleKeyboardEvent(SDL_Event &event) {
    if (this->game->getState() == Game::State::RUNNING) {
        auto key = event.key.keysym.sym;
        if (event.type == SDL_KEYDOWN) {
            if (key == SDLK_UP) {
                this->game->getPlayer().setMovement(Player::Movement::FORWARD);
            } else if (key == SDLK_DOWN) {
                this->game->getPlayer().setMovement(Player::Movement::BACK);
            }
            if (key == SDLK_LEFT) {
                this->game->getPlayer().setTurning(Player::Movement::TURN_LEFT);
            } else if (key == SDLK_RIGHT) {
                this->game->getPlayer().setTurning(Player::Movement::TURN_RIGHT);
            }
        } else {
            if (key == SDLK_UP || key == SDLK_DOWN)
                this->game->getPlayer().setMovement(Player::Movement::NONE);
            if (key == SDLK_LEFT || key == SDLK_RIGHT)
                this->game->getPlayer().setTurning(Player::Movement::NONE);
        }
    }
}

void GameWindow::chooseOption() {

}

void GameWindow::renderFrame() {
    switch (this->game->getState()){
        case Game::State::RUNNING:
            this->renderGameScreen();
            break;
        case Game::State::PAUSE:
            break;
        case Game::State::VICTORY:
            this->displayVictoryScreen();
            break;
        default:
            throw "Unknown game state!";
    }
}

void GameWindow::displayPauseManu() {

}

void GameWindow::renderGameScreen() {
    SDL_SetRenderDrawColor(this->renderer, 50, 160, 60, 200);
    for(auto sprite : this->sprites) {
        SDL_Texture *spriteTexture = SDL_CreateTextureFromSurface(renderer, sprite->getSurface());
        SDL_RenderCopyEx(this->renderer, spriteTexture, nullptr, &sprite->getVerticesPositions(), sprite->getAngle(),
                         nullptr,
                         SDL_FLIP_NONE);
        SDL_DestroyTexture(spriteTexture);
    }
}

void GameWindow::displayVictoryScreen() {
    this->renderGameScreen();
    SDL_RenderCopy(this->renderer, this->logoTexture, nullptr, &this->logo.getVerticesPositions());
}

void GameWindow::disappear() {

}