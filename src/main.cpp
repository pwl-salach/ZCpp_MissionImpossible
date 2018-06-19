#include "GUI/StartWindow.h"

//TODO change to "main" to compile on linux
int WinMain(int argc, char* argv[]) {
    auto *settings = new Settings();
    auto startWindow = new StartWindow(1024, 768, settings);
    startWindow->show();
    delete settings;
    delete startWindow;
    return 0;
}