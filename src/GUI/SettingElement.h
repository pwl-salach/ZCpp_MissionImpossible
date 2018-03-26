//
// Created by salach on 2/28/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_SETTINGELEMENT_H
#define ZCPP_MISSIONIMPOSSIBLE_SETTINGELEMENT_H

#include "MenuElement.h"
#include "../Utils/Dictionary.h"

template <typename T> class SettingElement: public MenuElement{

public:
    SettingElement(uint8_t id, const std::string &text, const SDL_Rect &verticesPosition, T setting)
            :MenuElement(id, text, verticesPosition), setting(setting) {
        backedUpValue = setting;
    }

    const std::string getText() const override {
        return text + ": " + getSettingText();
    }

    const std::string getSettingText() const{
        if (std::is_same<T, bool>::value){
            return setting ? Dictionary::YES : Dictionary::NO;
        }
        return std::to_string(setting);
    }

    T getSetting() const {
        return setting;
    }

    void increaseSettingValue(T limit){
        if (std::is_same<T, bool>::value){
            setting = true;
            return;
        }
        if (setting < limit){
            setting = setting + 1;
        }
    }

    void decreaseSettingValue(T limit){
        if (std::is_same<T, bool>::value){
            setting = false;
            return;
        }
        if (setting > limit){
            setting = setting - 1;
        }
    }

    void saveChanges(){
        backedUpValue = setting;
    }

    void resetValue(){
        setting = backedUpValue;
    }

private:
    T setting;
    T backedUpValue;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_SETTINGELEMENT_H
