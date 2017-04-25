#pragma once
#include "MainWindow.h"
#include <memory>

class CameraController {
public:
    void setMainWindow(std::shared_ptr<MainWindow> mw);
    static CameraController* getInstance();
private:
    CameraController();
    CameraController(std::shared_ptr<MainWindow> mw);
    static CameraController* instance;

    std::shared_ptr<MainWindow> mainWindow;
};
