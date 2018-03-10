//
// Created by Salach on 20.02.2018.
//

#include "MenuElement.h"


uint8_t MenuElement::getId() const {
    return id;
}

MenuElement::MenuElement(uint8_t id, const std::string &text, const SDL_Rect &verticesPosition)
        :id(id), text(text), verticesPositions(
        verticesPosition) {
    this->selected = false;
}

bool MenuElement::isSelected() const {
    return selected;
}

const std::string MenuElement::getText() const {
    return text;
}

const SDL_Rect &MenuElement::getVerticesPositions() const {
    return verticesPositions;
}

void MenuElement::setSelected(bool selected) {
    this->selected = selected;
}

MenuElement::~MenuElement() {

}
