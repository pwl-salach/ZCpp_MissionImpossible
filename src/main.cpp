#include "GUI/StartWindow.h"

//TODO change to "main" to compile on linux
int WinMain(int argc, char* argv[]) {
    StartWindow * startWindow = new StartWindow(1024, 768);
    startWindow->show();
    return 0;
}