//
// Created by salach on 3/1/18.
//

#include "GameWindow.h"

GameWindow::GameWindow(Game *pGame) : game(pGame) {
    resolutionX = game->getEnvironment().getSizeX();
    resolutionY = game->getEnvironment().getSizeY();
    frameRate = 60;
    preparePauseMenuElements();
    prepareSprites();
    SDL_Rect logoPos{resolutionX / 4, resolutionY / 8, resolutionX / 2, resolutionY / 4};
    logo = ImageElement("logo.png", logoPos);
    grass = ImageElement("grass.png", {0, 0, resolutionX, resolutionY});
}

void GameWindow::preparePauseMenuElements() {
    auto topMargin = uint16_t(resolutionY / 2);
    auto bottomMargin = uint16_t(resolutionY / 8);
    std::map<uint8_t, std::string> elementsBasicData{
            {PauseButtons::RESUME_GAME,   Dictionary::RESUME_GAME},
            {PauseButtons::RESTART_LEVEL, Dictionary::RESTART_LEVEL},
            {PauseButtons::MAIN_MENU,     Dictionary::MAIN_MENU},
            {PauseButtons::QUIT,          Dictionary::QUIT}
    };
    std::vector<SDL_Rect> menuElementsPositions = calculateMenuElementsCoordinates(elementsBasicData, topMargin,
                                                                                   bottomMargin);
    uint8_t i = 0;
    for (auto &pair : elementsBasicData) {
        pauseMenuElements.push_back(
                new MenuElement(pair.first, pair.second, menuElementsPositions.at(i)));
        i++;
    }
}

void GameWindow::prepareSprites() {
    for (auto object : game->getEnvironment().getObstacles()) {
        sprites.push_back(new Sprite(object));
    }
    //for(auto agent : game->getAgents()){
    //    sprites.push_back(new Sprite(agent));
    //}
    sprites.push_back(new Sprite(&game->getPlayer()));
}

void GameWindow::show() {
    window = SDL_CreateWindow(
            "Mission Impossible!!!",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            resolutionX,
            resolutionY,
            SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);
    logoTexture = SDL_CreateTextureFromSurface(renderer, logo.getSurface());
    grassTexture = SDL_CreateTextureFromSurface(renderer, grass.getSurface());
    visible = true;
    game->start();
    loop();
}

void GameWindow::loop() {
    Uint32 frameBeginning = 0;
    Uint32 frameEnd = 0;
    SDL_Event event{};
    while (visible) {
        frameBeginning = SDL_GetTicks();
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    game->quit();
                    visible = false;
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
    if (game->getState() == Game::State::RUNNING) {
        auto key = event.key.keysym.sym;
        if (event.type == SDL_KEYDOWN) {
            if (key == SDLK_UP) {
                game->getPlayer().setMovement(Player::Movement::FORWARD);
            } else if (key == SDLK_DOWN) {
                game->getPlayer().setMovement(Player::Movement::BACK);
            }
            if (key == SDLK_LEFT) {
                game->getPlayer().setTurning(Player::Movement::TURN_LEFT);
            } else if (key == SDLK_RIGHT) {
                game->getPlayer().setTurning(Player::Movement::TURN_RIGHT);
            }
        } else {
            if (key == SDLK_UP || key == SDLK_DOWN)
                game->getPlayer().setMovement(Player::Movement::NONE);
            if (key == SDLK_LEFT || key == SDLK_RIGHT)
                game->getPlayer().setTurning(Player::Movement::NONE);
        }
    }
}

void GameWindow::chooseOption() {

}

void GameWindow::renderFrame() {
    switch (game->getState()) {
        case Game::State::RUNNING:
            renderGameScreen();
            break;
        case Game::State::PAUSE:
            break;
        case Game::State::VICTORY:
            displayVictoryScreen();
            break;
        case Game::State::LOSE:
            displayLoseScreen();
            break;
        default:
            throw std::runtime_error("Unknown game state!");
    }
}

void GameWindow::displayPauseManu() {

}

void GameWindow::renderGameScreen() {
    SDL_RenderCopy(renderer, grassTexture, nullptr, &grass.getVerticesPositions());
    for (auto sprite : sprites) {
        SDL_Texture *spriteTexture = SDL_CreateTextureFromSurface(renderer, sprite->getSurface());
        SDL_RenderCopyEx(renderer, spriteTexture, nullptr, &sprite->getVerticesPositions(), sprite->getAngle(),
                         nullptr,
                         SDL_FLIP_NONE);
        SDL_DestroyTexture(spriteTexture);
    }
    if (game->getSettings()->isDebug()) {
        for (auto agent : game->getAgents()) {
            if (!agent->isPathStackEmpty()) {
                SDL_SetRenderDrawColor(renderer, 250, 250, 0, 200);
                SDL_RenderSetScale(renderer, 6, 6);
                auto dest = agent->getNextDestination();
                SDL_RenderDrawPoint(renderer, static_cast<int>(dest.getX() / 6), static_cast<int>(dest.getY() / 6));
            }
            if (agent->getPassingPoint().isSet()) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
                SDL_RenderDrawPoint(renderer, static_cast<int>(agent->getPassingPoint().getX() / 6),
                                    static_cast<int>(agent->getPassingPoint().getY() / 6));
            }
            SDL_RenderSetScale(renderer, 1, 1);
            SDL_SetRenderDrawColor(renderer, 100, 255, 255, 200);
            for (auto point : agent->getScanner().getScannedPoint()) {
                try {
                    SDL_RenderDrawPoint(renderer, static_cast<int>(point.getX()), static_cast<int>(point.getY()));
                } catch (std::runtime_error){
                    continue;
                }
            }
        }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void GameWindow::displayVictoryScreen() {
    renderGameScreen();
    SDL_RenderCopy(renderer, logoTexture, nullptr, &logo.getVerticesPositions());
}

void GameWindow::disappear() {

}

void GameWindow::displayLoseScreen() {
    renderGameScreen();
    SDL_RenderCopy(renderer, logoTexture, nullptr, &logo.getVerticesPositions());
}
