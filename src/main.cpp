#include "GUI/StartWindow.h"

//TODO change to "main" to compile on linux
int main(int argc, char* argv[]) {
    auto *settings = new Settings();
    auto * startWindow = new StartWindow(1024, 768, settings);
    startWindow->show();
    return 0;
}