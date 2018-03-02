//
// Created by Salach on 20.02.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_MANUELEMENT_H
#define ZCPP_MISSIONIMPOSSIBLE_MANUELEMENT_H

#include "ImageElement.h"
#include <string>

class MenuElement {
public:
    MenuElement(uint8_t id, const std::string &text, const SDL_Rect &verticesPosition);

    virtual ~MenuElement();

    uint8_t getId() const;
    bool isSelected() const;

    virtual const std::string getText() const;
    const SDL_Rect &getVerticesPosition() const;
    void setSelected(bool selected);

protected:
    std::string text;
    SDL_Rect verticesPosition;
    bool selected;
    uint8_t id;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_MANUELEMENT_H
