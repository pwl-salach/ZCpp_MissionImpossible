//
// Created by Salach on 18.02.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_STARTWINDOW_H
#define ZCPP_MISSIONIMPOSSIBLE_STARTWINDOW_H


#include "Window.h"
#include "MenuElement.h"
#include "../Logic/Settings.h"
#include "SettingElement.h"
#include <vector>
#include <map>

class StartWindow : public Window{
public:
    StartWindow(uint16_t resX, uint16_t resY, Settings *pSettings);

    virtual ~StartWindow();

    void show() override;
    void disappear() override;

private:
    enum MenuButtons{
        START_GAME = 0,
        SETTINGS = 1,
        MAP_NUMBER = 2,
        NUMBER_OF_AGENTS = 3,
        RANGE_OF_VIEW = 4,
        ANGLE_OF_VIEW = 5,
        DEBUG = 6,
        CANCEL = 7,
        ACCEPT = 8,
        QUIT = 9
    };
    void prepareMainMenuElements();
    void prepareSettingsMenuElements();
    void loop() override;
    void renderFrame() override;
    void handleKeyboardEvent(SDL_Event &event) override;
    void moveCursorUp();
    void moveCursorDown();
    void chooseOption();
    void goToSettings();
    void goToMainMenu();
    void selectFirstElement();
    void clearSelection();
    void handleLeftKeyboardButton();
    void handleRightKeyboardButton();
    void saveSettings();
    void cancelChanges();

    template <typename T> T getSettingValueAndApproveIt(uint8_t settingElementID){
        int index = 0;
        for(auto element : this->settingsMenuElements){
            if (element->getId() == settingElementID)
                break;
            index++;
        }
        SettingElement<T> *element = this->castMenuElementToSetting<T>(this->settingsMenuElements.at(index));
        element->saveChanges();
        return element->getSetting();
    }

    template <typename T> SettingElement<T>* castMenuElementToSetting(MenuElement *element) {
        return dynamic_cast<SettingElement<T>*>(element);
    }

    Settings *settings;
    std::vector<MenuElement*> mainMenuElements;
    std::vector<MenuElement*> settingsMenuElements;
    std::vector<MenuElement*> *visibleElements;
    uint8_t selectedElementIndex;
    TTF_Font *font;

    void startGame();
};


#endif //ZCPP_MISSIONIMPOSSIBLE_STARTWINDOW_H
