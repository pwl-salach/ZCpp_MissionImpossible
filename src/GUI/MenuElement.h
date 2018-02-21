//
// Created by Salach on 20.02.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_MANUELEMENT_H
#define ZCPP_MISSIONIMPOSSIBLE_MANUELEMENT_H

#include "ImageElement.h"
#include <string>

class MenuElement {
public:
    MenuElement(Uint8 id, const std::string &text, const SDL_Rect &verticesPosition);
    Uint8 getId() const;
    bool isSelected() const;
    const std::string &getText() const;
    const SDL_Rect &getVerticesPosition() const;
    void setSelected(bool selected);

private:
    std::string text;
    SDL_Rect verticesPosition;
    bool selected;
    Uint8 id;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_MANUELEMENT_H
