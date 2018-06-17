//
// Created by Salach on 18.02.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_WINDOW_H
#define ZCPP_MISSIONIMPOSSIBLE_WINDOW_H

#include "SDL2/SDL.h"
#include "ImageElement.h"
#include "MenuElement.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>
#include <vector>

class Window {
public:
    virtual void show() = 0;
    virtual void disappear() = 0;
protected:
    virtual void loop() = 0;
    virtual void handleKeyboardEvent(SDL_Event &event) = 0;
    virtual void renderFrame()=0;
    void initSDL();
    void quitSDL();
    void enforceFrameRate(Uint32 frameBeginning, Uint32 frameActionsEnd);
    std::vector<SDL_Rect> calculateMenuElementsCoordinates(std::map<uint8_t, std::string> &elementsTexts, uint16_t martinTop,
                                                           uint16_t marginBottom);
    uint16_t getElementWidth(std::string text, uint16_t elementHeight);

    SDL_Texture *logoTexture;
    TTF_Font *font;
    std::vector<MenuElement*> *visibleElements;
    ImageElement logo;
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool visible;
    uint8_t frameRate;
    uint16_t resolutionX;
    uint16_t resolutionY;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_WINDOW_H
