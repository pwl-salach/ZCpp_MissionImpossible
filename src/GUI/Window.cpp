//
// Created by Salach on 18.02.2018.
//

#include <SDL2/SDL_image.h>
#include <vector>
#include "Window.h"


void Window::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    int imgFlags = IMG_INIT_PNG;
    IMG_Init(imgFlags);
    TTF_Init();
}

void Window::enforceFrameRate(Uint32 frameBeginning, Uint32 frameActionsEnd) {
    Uint32 actualFrameDuration = frameBeginning - frameActionsEnd;
    Uint32 frameDuration = Uint32(1000/frameRate);

    if ( frameDuration > actualFrameDuration ){
        SDL_Delay( frameDuration - actualFrameDuration );
    }
}

std::vector<SDL_Rect> Window::calculateMenuElementsCoordinates(std::map<uint8_t, std::string> &elementsBasicData,
                                                                    uint16_t martinTop,
                                                                    uint16_t marginBottom) {
    uint8_t elementsCount = uint8_t(elementsBasicData.size());
    std::vector<SDL_Rect> ret;
    uint8_t elementSpaceProportions = 2;
    uint16_t space = resolutionY - martinTop - marginBottom;
    uint16_t elementsHeight = uint16_t(space/(elementsCount + (elementsCount - 1)/elementSpaceProportions));
    uint16_t verticalSpace = elementsHeight / elementSpaceProportions;
    uint16_t tempElementYCoord = martinTop;
    for (auto const &pair : elementsBasicData) {
        std::string text = pair.second;
        uint16_t elementsWidth = getElementWidth(text, elementsHeight);
        uint16_t elementsXCoord = uint16_t((resolutionX - elementsWidth) / 2);
        SDL_Rect tempRect = {elementsXCoord, tempElementYCoord, elementsWidth, elementsHeight};
        tempElementYCoord += elementsHeight + verticalSpace;
        ret.push_back(tempRect);
    }
    return ret;
}

uint16_t Window::getElementWidth(std::string text, uint16_t elementHeight){
    return static_cast<uint16_t>(text.length() * elementHeight * 0.75);
}

void Window::quitSDL() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
