//
// Created by Salach on 18.02.2018.
//

#include <SDL2/SDL_image.h>
#include "Window.h"


void Window::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    int imgFlags = IMG_INIT_PNG;
    IMG_Init( imgFlags );
    TTF_Init();
}

void Window::enforceFrameRate(Uint32 frameBeginning, Uint32 frameActionsEnd) {
    Uint32 actualFrameDuration = frameBeginning - frameActionsEnd;
    Uint32 frameDuration = Uint32(1000/this->frameRate);

    if ( frameDuration > actualFrameDuration ){
        SDL_Delay( frameDuration - actualFrameDuration );
    }
}

void Window::quitSDL() {
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
