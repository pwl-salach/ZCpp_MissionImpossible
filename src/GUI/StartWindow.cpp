//
// Created by Salach on 18.02.2018.
//

#include <iostream>
#include <map>
#include "StartWindow.h"
#include "../Utils/FileManager.h"
#include "GameWindow.h"

StartWindow::StartWindow(uint16_t resX, uint16_t resY, Settings *pSettings) {
    this->initSDL();
    this->resolutionX = resX;
    this->resolutionY = resY;
    this->frameRate = 60;
    this->prepareMainMenuElements();
    this->settings = pSettings;
    this->prepareSettingsMenuElements();
    SDL_Rect logoPos {this->resolutionX/4, this->resolutionY/8, this->resolutionX/2, this->resolutionY/4};
    this->logo = new ImageElement("logo.png", logoPos);
    this->font = FileManager::loadFont("KarmaFuture.ttf", 16);
}

void StartWindow::prepareMainMenuElements() {
    uint16_t topMargin = uint16_t(this->resolutionY / 2);
    uint16_t bottomMargin = uint16_t(this->resolutionY / 8);
    std::map<uint8_t, std::string> elementsBasicData {
            {MenuButtons::START_GAME, Dictionary::START_GAME},
            {MenuButtons::SETTINGS, Dictionary::SETTINGS},
            {MenuButtons::QUIT, Dictionary::QUIT}
    };
    std::vector<SDL_Rect> menuElementsPositions = this->calculateMenuElementsCoordinates(elementsBasicData, topMargin, bottomMargin);
    uint8_t i = 0;
    for (auto &pair : elementsBasicData) {
        this->mainMenuElements.push_back(
                new MenuElement(pair.first, pair.second, menuElementsPositions.at(i)));
        i++;
    }
}

void StartWindow::prepareSettingsMenuElements() {
    uint16_t topMargin = uint16_t(2 * this->resolutionY / 5);
    uint16_t bottomMargin = uint16_t(this->resolutionY / 4);
    std::map<uint8_t, std::string> elementsBasicData{
            {MenuButtons::MAP_NUMBER, Dictionary::MAP_NUMBER},
            {MenuButtons::NUMBER_OF_AGENTS, Dictionary::NUMBER_OF_AGENTS},
            {MenuButtons::RANGE_OF_VIEW,    Dictionary::RANGE_OF_VIEW},
            {MenuButtons::ANGLE_OF_VIEW,    Dictionary::ANGLE_OF_VIEW},
            {MenuButtons::DEBUG,            Dictionary::DEBUG}
    };
    std::vector<SDL_Rect> menuElementsPositions = this->calculateMenuElementsCoordinates(elementsBasicData, topMargin, bottomMargin);
    this->settingsMenuElements.push_back(new SettingElement<uint8_t>(MenuButtons::MAP_NUMBER, Dictionary::MAP_NUMBER, menuElementsPositions.at(0), this->settings->getMapNumber()));
    this->settingsMenuElements.push_back(new SettingElement<uint8_t>(MenuButtons::NUMBER_OF_AGENTS, Dictionary::NUMBER_OF_AGENTS, menuElementsPositions.at(1), this->settings->getNumberOfAgents()));
    this->settingsMenuElements.push_back(new SettingElement<uint16_t>(MenuButtons::RANGE_OF_VIEW, Dictionary::RANGE_OF_VIEW, menuElementsPositions.at(2), this->settings->getRangeOfView()));
    this->settingsMenuElements.push_back(new SettingElement<uint8_t>(MenuButtons::ANGLE_OF_VIEW, Dictionary::ANGLE_OF_VIEW, menuElementsPositions.at(3), this->settings->getAngleOfView()));
    this->settingsMenuElements.push_back(new SettingElement<bool>(MenuButtons::DEBUG, Dictionary::DEBUG, menuElementsPositions.at(4), this->settings->isDebug()));

    uint16_t elementHeight = uint16_t(this->settingsMenuElements.at(0)->getVerticesPosition().h);
    uint16_t acceptWidth = this->getElementWidth(Dictionary::ACCEPT, elementHeight);
    uint16_t cancelWidth = this->getElementWidth(Dictionary::CANCEL, elementHeight);
    uint16_t horizontalSpace = uint16_t(this->resolutionX / 10);
    uint16_t elementsYCoord = uint16_t(this->resolutionY - bottomMargin + elementHeight);
    uint16_t acceptXCoord = uint16_t((this->resolutionX + horizontalSpace) / 2);
    uint16_t cancelXCoord = uint16_t((this->resolutionX - horizontalSpace) / 2 - cancelWidth);
    this->settingsMenuElements.push_back(
            new MenuElement(MenuButtons::CANCEL, Dictionary::CANCEL, {cancelXCoord, elementsYCoord, cancelWidth, elementHeight}));
    this->settingsMenuElements.push_back(
            new MenuElement(MenuButtons::ACCEPT, Dictionary::ACCEPT, {acceptXCoord, elementsYCoord, acceptWidth, elementHeight}));
}

void StartWindow::show() {
    this->window= SDL_CreateWindow(
            "Mission Impossible!!!",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            this->resolutionX,
            this->resolutionY,
            SDL_WINDOW_OPENGL);
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    this->logoTexture = SDL_CreateTextureFromSurface(this->renderer, this->logo->getSurface());
    this->visible = true;
    this->goToMainMenu();
    this->loop();
}

void StartWindow::loop() {
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

void StartWindow::renderFrame() {
    //SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderCopy(this->renderer, this->logoTexture, NULL, &this->logo->getVerticesPosition());
    for (MenuElement *menuElement : *this->visibleElements){
        SDL_Color color = ( menuElement->isSelected() ? SDL_Color{255, 255, 255, 0}: SDL_Color{180, 180, 180, 0});
        SDL_Surface *textSurface = TTF_RenderText_Solid(this->font, menuElement->getText().c_str(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_RenderCopy(this->renderer, textTexture, NULL, &menuElement->getVerticesPosition());
    }
}

void StartWindow::handleKeyboardEvent(SDL_Event &event) {
    switch (event.key.keysym.sym){
        case SDLK_DOWN:
            this->moveCursorDown();
            break;
        case SDLK_UP:
            this->moveCursorUp();
            break;
        case SDLK_RETURN:
            this->chooseOption();
            break;
        case SDLK_LEFT:
            this->handleLeftKeyboardButton();
            break;
        case SDLK_RIGHT:
            this->handleRightKeyboardButton();
            break;
        default:
            break;
    }

}

void StartWindow::moveCursorUp() {
    this->clearSelection();
    if(this->selectedElementIndex == 0){
        this->selectedElementIndex = uint8_t(this->visibleElements->size() - 1);
    } else {
        this->selectedElementIndex--;
    }
    this->visibleElements->at(this->selectedElementIndex)->setSelected(true);
}

void StartWindow::moveCursorDown() {
    this->clearSelection();
    if (this->selectedElementIndex == this->visibleElements->size() - 1){
        this->selectedElementIndex = 0;
    } else {
        this->selectedElementIndex++;
    }
    this->visibleElements->at(this->selectedElementIndex)->setSelected(true);
}

void StartWindow::chooseOption() {
    switch (this->visibleElements->at(this->selectedElementIndex)->getId()){
        case MenuButtons::START_GAME :
            this->disappear();
            this->startGame();
            break;
        case MenuButtons::SETTINGS :
            this->clearSelection();
            this->goToSettings();
            break;
        case MenuButtons::QUIT :
            this->disappear();
            this->quitSDL();
            break;
        case MenuButtons::CANCEL:
            this->cancelChanges();
            this->clearSelection();
            this->goToMainMenu();
            break;
        case MenuButtons::ACCEPT:
            this->clearSelection();
            this->saveSettings();
            this->goToMainMenu();
            break;
        default:
            break;
    }
}

void StartWindow::goToMainMenu() {
    this->visibleElements = &this->mainMenuElements;
    this->selectFirstElement();
}

void StartWindow::goToSettings() {
    this->visibleElements = &this->settingsMenuElements;
    this->selectFirstElement();
}

void StartWindow::selectFirstElement(){
    this->selectedElementIndex = 0;
    this->visibleElements->at(this->selectedElementIndex)->setSelected(true);
}

void StartWindow::clearSelection() {
    this->visibleElements->at(this->selectedElementIndex)->setSelected(false);
}

void StartWindow::saveSettings() {
    this->settings->setNumberOfAgents(this->getSettingValueAndApproveIt<uint8_t>(MenuButtons::MAP_NUMBER));
    this->settings->setNumberOfAgents(this->getSettingValueAndApproveIt<uint8_t>(MenuButtons::NUMBER_OF_AGENTS));
    this->settings->setRangeOfView(this->getSettingValueAndApproveIt<uint16_t>(MenuButtons::RANGE_OF_VIEW));
    this->settings->setAngleOfView(this->getSettingValueAndApproveIt<uint8_t>(MenuButtons::ANGLE_OF_VIEW));
    this->settings->setDebug(this->getSettingValueAndApproveIt<bool>(MenuButtons::DEBUG));
}

void StartWindow::cancelChanges(){
    this->castMenuElementToSetting<uint8_t>(this->settingsMenuElements.at(0))->resetValue();
    this->castMenuElementToSetting<uint8_t>(this->settingsMenuElements.at(1))->resetValue();
    this->castMenuElementToSetting<uint16_t>(this->settingsMenuElements.at(2))->resetValue();
    this->castMenuElementToSetting<uint8_t>(this->settingsMenuElements.at(3))->resetValue();
    this->castMenuElementToSetting<bool>(this->settingsMenuElements.at(4))->resetValue();
}

void StartWindow::handleLeftKeyboardButton() {
    MenuElement *element = this->visibleElements->at(this->selectedElementIndex);
    switch (element->getId()){
        case MenuButtons::MAP_NUMBER :
            this->castMenuElementToSetting<uint8_t>(element)->decreaseSettingValue(this->settings->getMinManNumber());
            break;
        case MenuButtons::NUMBER_OF_AGENTS :
            this->castMenuElementToSetting<uint8_t>(element)->decreaseSettingValue(this->settings->getMinNumberOfAgents());
            break;
        case MenuButtons::RANGE_OF_VIEW :
            this->castMenuElementToSetting<uint16_t>(element)->decreaseSettingValue(this->settings->getMinRangeOfView());
            break;
        case MenuButtons::ANGLE_OF_VIEW :
            this->castMenuElementToSetting<uint8_t>(element)->decreaseSettingValue(this->settings->getMinAngleOfView());
            break;
        case MenuButtons::DEBUG :
            this->castMenuElementToSetting<bool>(element)->decreaseSettingValue(false);
            break;
        default:
            this->moveCursorUp();
            break;
    }
}

void StartWindow::handleRightKeyboardButton() {
    MenuElement *element = this->visibleElements->at(this->selectedElementIndex);
    switch (element->getId()){
        case MenuButtons::MAP_NUMBER :
            this->castMenuElementToSetting<uint8_t>(element)->increaseSettingValue(this->settings->getMaxManNumber());
            break;
        case MenuButtons::NUMBER_OF_AGENTS :
            this->castMenuElementToSetting<uint8_t>(element)->increaseSettingValue(this->settings->getMaxNumberOfAgents());
            break;
        case MenuButtons::ANGLE_OF_VIEW :
            this->castMenuElementToSetting<uint16_t>(element)->increaseSettingValue(this->settings->getMaxRangeOfView());
            break;
        case MenuButtons::RANGE_OF_VIEW :
            this->castMenuElementToSetting<uint8_t>(element)->increaseSettingValue(this->settings->getMaxAngleOfView());
            break;
        case MenuButtons::DEBUG :
            this->castMenuElementToSetting<bool>(element)->increaseSettingValue(true);
            break;
        default:
            this->moveCursorDown();
            break;
    }
}

void StartWindow::disappear() {
    this->visible = false;
    //delete this->visibleElements;
    SDL_DestroyWindow(this->window);
}

void StartWindow::startGame() {
    Game *game = new Game(this->settings);
    GameWindow *gameWindow = new GameWindow(game);
}

StartWindow::~StartWindow() {
    this->quitSDL();
}
