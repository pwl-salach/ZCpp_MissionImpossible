//
// Created by salach on 3/1/18.
//

#include "GameWindow.h"
#include "../Utils/FileManager.h"

GameWindow::GameWindow(Game *pGame, StartWindow *pStartWindow) : game(pGame), startWindow(pStartWindow) {
    resolutionX = game->getEnvironment().getSizeX();
    resolutionY = game->getEnvironment().getSizeY();
    frameRate = 60;
    preparePauseMenuElements();
    prepareEndGameElements();
    prepareSprites();
    SDL_Rect logoPos{resolutionX / 4, resolutionY / 8, resolutionX / 2, resolutionY / 4};
    logo = ImageElement("logo.png", logoPos);
    grass = ImageElement("grass.png", {0, 0, resolutionX, resolutionY});
    font = FileManager::loadFont("KarmaFuture.ttf", 16);
}

void GameWindow::preparePauseMenuElements() {
    std::map<uint8_t, std::string> elementsBasicData{
            {PauseButtons::RESUME_GAME,   Dictionary::RESUME_GAME},
            {PauseButtons::RESTART_LEVEL, Dictionary::RESTART_LEVEL},
            {PauseButtons::MAIN_MENU,     Dictionary::MAIN_MENU},
            {PauseButtons::QUIT,          Dictionary::QUIT}
    };
    prepareMenuElements(elementsBasicData, pauseMenuElements);
}

void GameWindow::prepareEndGameElements() {
    std::map<uint8_t, std::string> elementsBasicData{
            {PauseButtons::RESTART_LEVEL, Dictionary::RESTART_LEVEL},
            {PauseButtons::MAIN_MENU,     Dictionary::MAIN_MENU},
            {PauseButtons::QUIT,          Dictionary::QUIT}
    };
    prepareMenuElements(elementsBasicData, endGameElements);
}

void
GameWindow::prepareMenuElements(std::map<uint8_t, std::string> elementsData, std::vector<MenuElement *> &container) {
    auto topMargin = uint16_t(resolutionY / 2);
    auto botmMargin = uint16_t(resolutionY / 8);
    std::vector<SDL_Rect> menuElementsPositions = calculateMenuElementsCoordinates(elementsData, topMargin, botmMargin);
    uint8_t i = 0;
    for (auto &pair : elementsData) {
        container.push_back(
                new MenuElement(pair.first, pair.second, menuElementsPositions.at(i)));
        i++;
    }
}

void GameWindow::prepareSprites() {
    for (auto object : game->getEnvironment().getObstacles()) {
        sprites.push_back(new Sprite(object));
    }
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
    visibleElements = &endGameElements;
    selectFirstElement();
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
                    visible = false;
                    game->quit();
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
    auto key = event.key.keysym.sym;
    if (game->getState() == Game::State::RUNNING) {
        if (event.type == SDL_KEYDOWN) {
            switch (key) {
                case SDLK_UP:
                    game->getPlayer().setMovement(Player::Movement::FORWARD);
                    break;
                case SDLK_DOWN:
                    game->getPlayer().setMovement(Player::Movement::BACK);
                    break;
                case SDLK_LEFT:
                    game->getPlayer().setTurning(Player::Movement::TURN_LEFT);
                    break;
                case SDLK_RIGHT:
                    game->getPlayer().setTurning(Player::Movement::TURN_RIGHT);
                    break;
                case SDLK_ESCAPE:
                    visibleElements = &pauseMenuElements;
                    selectFirstElement();
                    game->pause();
                    break;
                default:
                    break;
            }
        } else {
            if (key == SDLK_UP || key == SDLK_DOWN)
                game->getPlayer().setMovement(Player::Movement::NONE);
            if (key == SDLK_LEFT || key == SDLK_RIGHT)
                game->getPlayer().setTurning(Player::Movement::NONE);
        }
    } else if (game->getState() == Game::State::PAUSE ||
               game->getState() == Game::State::VICTORY ||
               game->getState() == Game::State::LOSE) {
        if (event.type == SDL_KEYDOWN) {
            switch (key) {
                case SDLK_ESCAPE:
                    resumeGame();
                    break;
                case SDLK_DOWN:
                    moveCursorDown();
                    break;
                case SDLK_UP:
                    moveCursorUp();
                    break;
                case SDLK_RETURN:
                    chooseOption();
                    break;
                default:
                    break;
            }
        }
    }
}


void GameWindow::chooseOption() {
    switch (visibleElements->at(selectedElementIndex)->getId()) {
        case PauseButtons::RESUME_GAME :
            resumeGame();
            break;
        case PauseButtons::RESTART_LEVEL :
            restartLevel();
            break;
        case PauseButtons::MAIN_MENU:
            goBackToMainMenu();
            break;
        case PauseButtons::QUIT :
            disappear();
            game->quit();
            break;
        default:
            break;
    }
}

void GameWindow::renderFrame() {
    switch (game->getState()) {
        case Game::State::RUNNING:
            renderGameScreen();
            break;
        case Game::State::PAUSE:
            displayPauseMenu();
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

void GameWindow::displayPauseMenu() {
    renderGameScreen();
    SDL_RenderCopy(renderer, logoTexture, nullptr, &logo.getVerticesPositions());
    for (MenuElement *menuElement : *visibleElements) {
        SDL_Color color = (menuElement->isSelected() ? SDL_Color{255, 255, 255, 0} : SDL_Color{180, 180, 180, 0});
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, menuElement->getText().c_str(), color);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_RenderCopy(renderer, textTexture, nullptr, &menuElement->getVerticesPositions());
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }
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
                auto dest = agent->getNextDestination();
                SDL_SetRenderDrawColor(renderer, 250, 250, 0, 200);
                SDL_RenderSetScale(renderer, 6, 6);
                SDL_RenderDrawPoint(renderer, static_cast<int>(dest.getX() / 6), static_cast<int>(dest.getY() / 6));
            }
            if (agent->getPassingPoint().isSet()) {
                auto passingPoint = agent->getPassingPoint();
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
                SDL_RenderDrawPoint(renderer, static_cast<int>(passingPoint.getX() / 6),
                                    static_cast<int>(passingPoint.getY() / 6));
            }
            SDL_RenderSetScale(renderer, 1, 1);
            SDL_SetRenderDrawColor(renderer, 100, 255, 255, 200);
            for (auto point : agent->getScanner().getScannedPoints()) {
                try {
                    SDL_RenderDrawPoint(renderer, static_cast<int>(point.getX()), static_cast<int>(point.getY()));
                } catch (std::runtime_error &err) { ; }
            }
        }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void GameWindow::displayVictoryScreen() {
    displayEndGameMenu();
}

void GameWindow::displayLoseScreen() {
    displayEndGameMenu();
}

void GameWindow::displayEndGameMenu() {
    renderGameScreen();
    SDL_RenderCopy(renderer, logoTexture, nullptr, &logo.getVerticesPositions());
    for (MenuElement *menuElement : *visibleElements) {
        SDL_Color color = (menuElement->isSelected() ? SDL_Color{255, 255, 255, 0} : SDL_Color{180, 180, 180, 0});
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, menuElement->getText().c_str(), color);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_RenderCopy(renderer, textTexture, nullptr, &menuElement->getVerticesPositions());
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }
}

void GameWindow::goBackToMainMenu() {
    disappear();
    game->quit();
    delete game;
    startWindow->show();
}

void GameWindow::restartLevel() {
    auto settings = game->getSettings();
    game->quit();
    delete game;
    std::vector<Agent *> agents;
    for (int i = 0; i < settings->getNumberOfAgents(); i++) {
        auto agent = new Agent(settings->getRangeOfView(), settings->getAngleOfView());
        agents.push_back(agent);
    }
    game = new Game(settings, agents);
    visible = false;
    game->start();
    removeSprites();
    prepareSprites();
    clearSelection();
    visibleElements = &endGameElements;
    visible = true;
    loop();
}

void GameWindow::removeSprites() {
    for (auto sprite : sprites) {
        delete sprite;
    }
    sprites.clear();
}

void GameWindow::resumeGame() {
    pauseMenuElements.at(selectedElementIndex)->setSelected(false);
    visibleElements = &endGameElements;
    game->resume();
}
