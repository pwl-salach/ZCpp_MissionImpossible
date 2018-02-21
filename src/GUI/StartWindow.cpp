//
// Created by Salach on 18.02.2018.
//

#include <iostream>
#include <map>
#include "StartWindow.h"
#include "../Utils/Dictionary.h"

StartWindow::StartWindow(Uint16 resX, Uint16 resY) {
    this->initSDL();
    this->resolutionX = resX;
    this->resolutionY = resY;
    this->frameRate = 60;
    this->prepareMainMenuElements();
    this->prepareSettingsMenuElements();
    this->goToMainMenu();
    SDL_Rect logoPos {this->resolutionX/4, this->resolutionY/8, this->resolutionX/2, this->resolutionY/4};
    this->logo = new ImageElement("../resources/logo.png", logoPos);
    this->font = TTF_OpenFont("../resources/KarmaFuture.ttf", 16);
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
        default:
            break;
    }

}

void StartWindow::disappear() {
    this->visible = false;
    SDL_DestroyWindow(this->window);
}

void StartWindow::renderFrame() {
    //SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderCopy(this->renderer, this->logoTexture, NULL, &this->logo->getverticesPosition());
    for (MenuElement *menuElement : *this->visibleElements){
        SDL_Color color = ( menuElement->isSelected() ? SDL_Color{255, 255, 255, 0}: SDL_Color{180, 180, 180, 0});
        SDL_Surface *textSurface = TTF_RenderText_Solid(this->font, menuElement->getText().c_str(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_RenderCopy(this->renderer, textTexture, NULL, &menuElement->getVerticesPosition());
    }
}

void StartWindow::prepareMainMenuElements() {
    Uint16 topMargin = Uint16(this->resolutionY / 2);
    Uint16 bottomMargin = Uint16(this->resolutionY / 8);
    std::map<Uint8, std::string> elementsBasicData {
            {MenuButtons::START_GAME, Dictionary::START_GAME},
            {MenuButtons::SETTINGS, Dictionary::SETTINGS},
            {MenuButtons::QUIT, Dictionary::QUIT}
    };
    this->prepareRegularMenuPart(this->mainMenuElements, elementsBasicData, bottomMargin, topMargin);
}

void StartWindow::prepareSettingsMenuElements() {
    Uint16 topMargin = Uint16(this->resolutionY / 2);
    Uint16 bottomMargin = Uint16(this->resolutionY / 4);
    std::map<Uint8, std::__cxx11::string> elementsBasicData{
            {NUMBER_OF_AGENTS, Dictionary::NUMBER_OF_AGENTS},
            {RANGE_OF_VIEW,    Dictionary::RANGE_OF_VIEW},
            {ANGLE_OF_VIEW,    Dictionary::ANGLE_OF_VIEW},
            {DEBUG,            Dictionary::DEBUG}
    };
    this->prepareRegularMenuPart(this->settingsMenuElements, elementsBasicData, bottomMargin, topMargin);
    Uint16 elementHeight = Uint16(this->settingsMenuElements.at(0)->getVerticesPosition().h);
    Uint16 acceptWidth = this->getElementWidth(Dictionary::ACCEPT, elementHeight);
    Uint16 cancelWidth = this->getElementWidth(Dictionary::CANCEL, elementHeight);
    Uint16 horisontalSpace = Uint16(this->resolutionX / 10);
    Uint16 elementsYCoord = Uint16(this->resolutionY - bottomMargin + elementHeight);
    Uint16 acceptXCoord = Uint16((this->resolutionX + horisontalSpace) / 2);
    Uint16 cancelXCoord = Uint16((this->resolutionX - horisontalSpace) / 2 - cancelWidth);
    this->settingsMenuElements.push_back(
            new MenuElement(MenuButtons::ACCEPT, Dictionary::ACCEPT, {acceptXCoord, elementsYCoord, acceptWidth, elementHeight}));
    this->settingsMenuElements.push_back(
            new MenuElement(MenuButtons::CANCEL, Dictionary::CANCEL, {cancelXCoord, elementsYCoord, cancelWidth, elementHeight}));
}

void StartWindow::prepareRegularMenuPart(std::vector<MenuElement *> &menuElements,
                                         std::map<Uint8, std::string> &elementsBasicData, Uint16 &bottomMargin,
                                         Uint16 &topMargin) {
    std::vector<SDL_Rect> menuElementsPositions = this->calculateMenuElementsCoordinates(elementsBasicData, topMargin, bottomMargin);
    Uint8 i = 0;
    for (auto &pair : elementsBasicData) {
        menuElements.push_back(
                new MenuElement(pair.first, pair.second, menuElementsPositions.at(i)));
        i++;
    }
}

std::vector<SDL_Rect> StartWindow::calculateMenuElementsCoordinates(std::map<Uint8, std::string> &elementsBasicData,
                                                                    Uint16 martinTop,
                                                                    Uint16 marginBottom) {
    int elementsCount = elementsBasicData.size();
    std::vector<SDL_Rect> ret;
    Uint8 elementSpaceProportions = 2;
    Uint16 space = this->resolutionY - martinTop - marginBottom;
    Uint16 elementsHeight = Uint16(space/(elementsCount + (elementsCount - 1)/elementSpaceProportions));
    Uint16 verticalSpace = elementsHeight / elementSpaceProportions;
    Uint16 tempElementYCoord = martinTop;
    for (auto const &pair : elementsBasicData) {
        std::string text = pair.second;
        Uint16 elementsWidth = this->getElementWidth(text, elementsHeight);
        Uint16 elementsXCoord = Uint16((this->resolutionX - elementsWidth) / 2);
        SDL_Rect tempRect = {elementsXCoord, tempElementYCoord, elementsWidth, elementsHeight};
        tempElementYCoord += elementsHeight + verticalSpace;
        ret.push_back(tempRect);
    }
    return ret;
}

Uint16 StartWindow::getElementWidth(std::string text, Uint16 elementHeight){
    return static_cast<Uint16>(text.length() * elementHeight * 0.75);
}

void StartWindow::moveCursorUp() {
    Uint8 temp = this->selectedElementIndex;
    if(this->selectedElementIndex == 0){
        this->selectedElementIndex = Uint8(this->visibleElements->size() - 1);
    } else {
        this->selectedElementIndex--;
    }
    this->visibleElements->at(temp)->setSelected(false);
    this->visibleElements->at(this->selectedElementIndex)->setSelected(true);
}

void StartWindow::moveCursorDown() {
    Uint8 temp = this->selectedElementIndex;
    if (this->selectedElementIndex == this->visibleElements->size() - 1){
        this->selectedElementIndex = 0;
    } else {
        this->selectedElementIndex++;
    }
    this->visibleElements->at(temp)->setSelected(false);
    this->visibleElements->at(this->selectedElementIndex)->setSelected(true);
}

void StartWindow::chooseOption() {
    switch (this->visibleElements->at(this->selectedElementIndex)->getId()){
        case MenuButtons::START_GAME :
            break;
        case MenuButtons::SETTINGS :
            this->visibleElements->at(this->selectedElementIndex)->setSelected(false);
            this->goToSettings();
            break;
        case MenuButtons::QUIT :
            this->disappear();
            this->quitSDL();
            break;
        case MenuButtons::CANCEL:
            this->visibleElements->at(this->selectedElementIndex)->setSelected(false);
            this->goToMainMenu();
            break;
        case MenuButtons::ACCEPT:
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

void StartWindow::saveSettings() {

}
