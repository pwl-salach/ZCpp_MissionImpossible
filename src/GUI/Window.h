//
// Created by Salach on 18.02.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_WINDOW_H
#define ZCPP_MISSIONIMPOSSIBLE_WINDOW_H

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

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

    SDL_Window *window;
    SDL_Renderer *renderer;
    bool visible;
    Uint8 frameRate;
    Uint16 resolutionX;
    Uint16 resolutionY;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_WINDOW_H
