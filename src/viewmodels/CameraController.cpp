#include "CameraController.h"

CameraController* CameraController::instance = nullptr;

CameraController* CameraController::getInstance() {
    if (!instance)
        instance = new CameraController;
    return instance;
}

CameraController::CameraController() {}

CameraController::CameraController(std::shared_ptr<MainWindow> mw) {
    mainWindow = mw;
}

void CameraController::setMainWindow(std::shared_ptr<MainWindow> mw) {
    mainWindow = mw;
}
