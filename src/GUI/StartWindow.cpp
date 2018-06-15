//
// Created by Salach on 18.02.2018.
//

#include <iostream>
#include <map>
#include "StartWindow.h"
#include "../Utils/FileManager.h"
#include "GameWindow.h"

StartWindow::StartWindow(uint16_t resX, uint16_t resY, Settings *pSettings) {
    initSDL();
    resolutionX = resX;
    resolutionY = resY;
    frameRate = 60;
    prepareMainMenuElements();
    settings = pSettings;
    prepareSettingsMenuElements();
    SDL_Rect logoPos {resolutionX/4, resolutionY/8, resolutionX/2, resolutionY/4};
    logo = ImageElement("logo.png", logoPos);
    font = FileManager::loadFont("KarmaFuture.ttf", 16);
}

void StartWindow::prepareMainMenuElements() {
    auto topMargin = uint16_t(resolutionY / 2);
    auto bottomMargin = uint16_t(resolutionY / 8);
    std::map<uint8_t, std::string> elementsBasicData {
            {MenuButtons::START_GAME, Dictionary::START_GAME},
            {MenuButtons::SETTINGS, Dictionary::SETTINGS},
            {MenuButtons::QUIT, Dictionary::QUIT}
    };
    std::vector<SDL_Rect> menuElementsPositions = calculateMenuElementsCoordinates(elementsBasicData, topMargin, bottomMargin);
    uint8_t i = 0;
    for (auto &pair : elementsBasicData) {
        mainMenuElements.push_back(
                new MenuElement(pair.first, pair.second, menuElementsPositions.at(i)));
        i++;
    }
}

void StartWindow::prepareSettingsMenuElements() {
    auto topMargin = uint16_t(2 * resolutionY / 5);
    auto bottomMargin = uint16_t(resolutionY / 4);
    std::map<uint8_t, std::string> elementsBasicData{
            {MenuButtons::environment_NUMBER, Dictionary::environment_NUMBER},
            {MenuButtons::NUMBER_OF_AGENTS, Dictionary::NUMBER_OF_AGENTS},
            {MenuButtons::RANGE_OF_VIEW,    Dictionary::RANGE_OF_VIEW},
            {MenuButtons::ANGLE_OF_VIEW,    Dictionary::ANGLE_OF_VIEW},
            {MenuButtons::DEBUG,            Dictionary::DEBUG}
    };
    std::vector<SDL_Rect> menuElementsPositions = calculateMenuElementsCoordinates(elementsBasicData, topMargin, bottomMargin);
    settingsMenuElements.push_back(new SettingElement<uint8_t>(MenuButtons::environment_NUMBER,
                                                                     Dictionary::environment_NUMBER,
                                                                     menuElementsPositions.at(0),
                                                                     settings->getEnvironmentNumber()));
    settingsMenuElements.push_back(new SettingElement<uint8_t>(MenuButtons::NUMBER_OF_AGENTS,
                                                                     Dictionary::NUMBER_OF_AGENTS,
                                                                     menuElementsPositions.at(1),
                                                                     settings->getNumberOfAgents()));
    settingsMenuElements.push_back(new SettingElement<uint16_t>(MenuButtons::RANGE_OF_VIEW,
                                                                      Dictionary::RANGE_OF_VIEW,
                                                                      menuElementsPositions.at(2),
                                                                      settings->getRangeOfView()));
    settingsMenuElements.push_back(new SettingElement<uint8_t>(MenuButtons::ANGLE_OF_VIEW,
                                                                     Dictionary::ANGLE_OF_VIEW,
                                                                     menuElementsPositions.at(3),
                                                                     settings->getAngleOfView()));
    settingsMenuElements.push_back(new SettingElement<bool>(MenuButtons::DEBUG,
                                                                  Dictionary::DEBUG,
                                                                  menuElementsPositions.at(4),
                                                                  settings->isDebug()));

    auto elementHeight = uint16_t(settingsMenuElements.at(0)->getVerticesPositions().h);
    auto acceptWidth = getElementWidth(Dictionary::ACCEPT, elementHeight);
    auto cancelWidth = getElementWidth(Dictionary::CANCEL, elementHeight);
    auto horizontalSpace = uint16_t(resolutionX / 10);
    auto elementsYCoord = uint16_t(resolutionY - bottomMargin + elementHeight);
    auto acceptXCoord = uint16_t((resolutionX + horizontalSpace) / 2);
    auto cancelXCoord = uint16_t((resolutionX - horizontalSpace) / 2 - cancelWidth);
    settingsMenuElements.push_back(
            new MenuElement(MenuButtons::CANCEL, Dictionary::CANCEL, {cancelXCoord, elementsYCoord, cancelWidth, elementHeight}));
    settingsMenuElements.push_back(
            new MenuElement(MenuButtons::ACCEPT, Dictionary::ACCEPT, {acceptXCoord, elementsYCoord, acceptWidth, elementHeight}));
}

void StartWindow::show() {
    window= SDL_CreateWindow(
            "Mission Impossible!!!",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            resolutionX,
            resolutionY,
            SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);
    logoTexture = SDL_CreateTextureFromSurface(renderer, logo.getSurface());
    visible = true;
    goToMainMenu();
    loop();
}

void StartWindow::loop() {
    Uint32  frameBeginning = 0;
    Uint32 frameEnd = 0;
    SDL_Event event{};
    while(visible) {
        frameBeginning = SDL_GetTicks();
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    visible = false;
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
    SDL_RenderCopy(renderer, logoTexture, nullptr, &logo.getVerticesPositions());
    for (MenuElement *menuElement : *visibleElements){
        SDL_Color color = ( menuElement->isSelected() ? SDL_Color{255, 255, 255, 0}: SDL_Color{180, 180, 180, 0});
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, menuElement->getText().c_str(), color);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_RenderCopy(renderer, textTexture, nullptr, &menuElement->getVerticesPositions());
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }
}

void StartWindow::handleKeyboardEvent(SDL_Event &event) {
    switch (event.key.keysym.sym){
        case SDLK_DOWN:
            moveCursorDown();
            break;
        case SDLK_UP:
            moveCursorUp();
            break;
        case SDLK_RETURN:
            chooseOption();
            break;
        case SDLK_LEFT:
            handleLeftKeyboardButton();
            break;
        case SDLK_RIGHT:
            handleRightKeyboardButton();
            break;
        default:
            break;
    }

}

void StartWindow::moveCursorUp() {
    clearSelection();
    if(selectedElementIndex == 0){
        selectedElementIndex = uint8_t(visibleElements->size() - 1);
    } else {
        selectedElementIndex--;
    }
    visibleElements->at(selectedElementIndex)->setSelected(true);
}

void StartWindow::moveCursorDown() {
    clearSelection();
    if (selectedElementIndex == visibleElements->size() - 1){
        selectedElementIndex = 0;
    } else {
        selectedElementIndex++;
    }
    visibleElements->at(selectedElementIndex)->setSelected(true);
}

void StartWindow::chooseOption() {
    switch (visibleElements->at(selectedElementIndex)->getId()){
        case MenuButtons::START_GAME :
            disappear();
            startGame();
            break;
        case MenuButtons::SETTINGS :
            clearSelection();
            goToSettings();
            break;
        case MenuButtons::QUIT :
            disappear();
            quitSDL();
            break;
        case MenuButtons::CANCEL:
            cancelChanges();
            clearSelection();
            goToMainMenu();
            break;
        case MenuButtons::ACCEPT:
            clearSelection();
            saveSettings();
            goToMainMenu();
            break;
        default:
            break;
    }
}

void StartWindow::goToMainMenu() {
    visibleElements = &mainMenuElements;
    selectFirstElement();
}

void StartWindow::goToSettings() {
    visibleElements = &settingsMenuElements;
    selectFirstElement();
}

void StartWindow::selectFirstElement(){
    selectedElementIndex = 0;
    visibleElements->at(selectedElementIndex)->setSelected(true);
}

void StartWindow::clearSelection() {
    visibleElements->at(selectedElementIndex)->setSelected(false);
}

void StartWindow::saveSettings() {
    settings->setNumberOfAgents(getSettingValueAndApproveIt<uint8_t>(MenuButtons::environment_NUMBER));
    settings->setNumberOfAgents(getSettingValueAndApproveIt<uint8_t>(MenuButtons::NUMBER_OF_AGENTS));
    settings->setRangeOfView(getSettingValueAndApproveIt<uint16_t>(MenuButtons::RANGE_OF_VIEW));
    settings->setAngleOfView(getSettingValueAndApproveIt<uint8_t>(MenuButtons::ANGLE_OF_VIEW));
    settings->setDebug(getSettingValueAndApproveIt<bool>(MenuButtons::DEBUG));
}

void StartWindow::cancelChanges(){
    castMenuElementToSetting<uint8_t>(settingsMenuElements.at(0))->resetValue();
    castMenuElementToSetting<uint8_t>(settingsMenuElements.at(1))->resetValue();
    castMenuElementToSetting<uint16_t>(settingsMenuElements.at(2))->resetValue();
    castMenuElementToSetting<uint8_t>(settingsMenuElements.at(3))->resetValue();
    castMenuElementToSetting<bool>(settingsMenuElements.at(4))->resetValue();
}

void StartWindow::handleLeftKeyboardButton() {
    MenuElement *element = visibleElements->at(selectedElementIndex);
    switch (element->getId()){
        case MenuButtons::environment_NUMBER :
            castMenuElementToSetting<uint8_t>(element)->decreaseSettingValue(settings->getMinManNumber());
            break;
        case MenuButtons::NUMBER_OF_AGENTS :
            castMenuElementToSetting<uint8_t>(element)->decreaseSettingValue(settings->getMinNumberOfAgents());
            break;
        case MenuButtons::RANGE_OF_VIEW :
            castMenuElementToSetting<uint16_t>(element)->decreaseSettingValue(settings->getMinRangeOfView());
            break;
        case MenuButtons::ANGLE_OF_VIEW :
            castMenuElementToSetting<uint8_t>(element)->decreaseSettingValue(settings->getMinAngleOfView());
            break;
        case MenuButtons::DEBUG :
            castMenuElementToSetting<bool>(element)->decreaseSettingValue(false);
            break;
        default:
            moveCursorUp();
            break;
    }
}

void StartWindow::handleRightKeyboardButton() {
    MenuElement *element = visibleElements->at(selectedElementIndex);
    switch (element->getId()){
        case MenuButtons::environment_NUMBER :
            castMenuElementToSetting<uint8_t>(element)->increaseSettingValue(settings->getMaxManNumber());
            break;
        case MenuButtons::NUMBER_OF_AGENTS :
            castMenuElementToSetting<uint8_t>(element)->increaseSettingValue(settings->getMaxNumberOfAgents());
            break;
        case MenuButtons::RANGE_OF_VIEW:
            castMenuElementToSetting<uint16_t>(element)->increaseSettingValue(settings->getMaxRangeOfView());
            break;
        case MenuButtons::ANGLE_OF_VIEW:
            castMenuElementToSetting<uint8_t>(element)->increaseSettingValue(settings->getMaxAngleOfView());
            break;
        case MenuButtons::DEBUG :
            castMenuElementToSetting<bool>(element)->increaseSettingValue(true);
            break;
        default:
            moveCursorDown();
            break;
    }
}

void StartWindow::disappear() {
    visible = false;
    //delete visibleElements;
    SDL_DestroyWindow(window);
}

void StartWindow::startGame() {
    std::vector<Agent*> agents;
    for(int i=0; i<settings->getNumberOfAgents(); i++){
        auto agent = new Agent(settings->getRangeOfView(), settings->getAngleOfView());
        agents.push_back(agent);
    }
    auto *game = new Game(settings, agents);
    auto *gameWindow = new GameWindow(game);
    gameWindow->show();
}

StartWindow::~StartWindow() {
    quitSDL();
}
