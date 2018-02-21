//
// Created by Salach on 18.02.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_STARTWINDOW_H
#define ZCPP_MISSIONIMPOSSIBLE_STARTWINDOW_H


#include "Window.h"
#include "MenuElement.h"
#include <vector>
#include <map>

class StartWindow : public Window{
public:
    StartWindow(Uint16 resX, Uint16 resY);
    void show() override;
    void disappear() override;

private:
    enum MenuButtons{
        START_GAME = 0,
        SETTINGS = 1,
        NUMBER_OF_AGENTS = 2,
        RANGE_OF_VIEW = 3,
        ANGLE_OF_VIEW = 4,
        DEBUG = 5,
        ACCEPT = 6,
        CANCEL = 7,
        QUIT = 8
    };
    void prepareMainMenuElements();
    void prepareSettingsMenuElements();
    std::vector<SDL_Rect> calculateMenuElementsCoordinates(std::map<Uint8, std::string> &elementsTexts, Uint16 martinTop,
                                                           Uint16 marginBottom);
    void loop() override;
    void renderFrame() override;
    void handleKeyboardEvent(SDL_Event &event) override;
    void moveCursorUp();
    void moveCursorDown();
    void chooseOption();
    void goToSettings();
    void goToMainMenu();
    SDL_Texture *logoTexture;
    ImageElement *logo;
    std::vector<MenuElement*> mainMenuElements;
    std::vector<MenuElement*> settingsMenuElements;
    std::vector<MenuElement*> *visibleElements;
    Uint8 selectedElementIndex;
    TTF_Font *font;

    Uint16 getElementWidth(std::string text, Uint16 elementHeight);

    void selectFirstElement();

    void saveSettings();

    void prepareRegularMenuPart(std::vector<MenuElement *> &menuElements,
                                    std::map<Uint8, std::string> &elementsBasicData, Uint16 &bottomMargin,
                                    Uint16 &topMargin);
};


#endif //ZCPP_MISSIONIMPOSSIBLE_STARTWINDOW_H
