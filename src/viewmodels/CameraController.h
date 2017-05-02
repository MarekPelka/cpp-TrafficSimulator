#pragma once
#include "../models/Camera.h"
#include "MainWindow.h"
#include <list>
#include <memory>
#include <thread>
#include <windows.h>

class CameraController {
public:
    void setMainWindow(std::shared_ptr<MainWindow> mw);
    static CameraController* getInstance();
    void addCamera(Camera camera);
    void deleteCamera(Camera camera);
    void clearController();
    void updateObservations();

private:
    CameraController();
    CameraController(std::shared_ptr<MainWindow> mw);
    static CameraController* instance;
    std::shared_ptr<MainWindow> mainWindow;

    std::list<Camera> cameras;
};
