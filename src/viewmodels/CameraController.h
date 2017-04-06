#pragma once
#include "MainWindow.h"

class CameraController
{
public:
    void setMainWindow(MainWindow *mw);
    static CameraController* getInstance();
private:
    CameraController();
    CameraController(MainWindow *mw);
    static CameraController* instance;

    MainWindow *mainWindow;
};
