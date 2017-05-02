#include "CameraController.h"

CameraController* CameraController::instance = nullptr;

CameraController* CameraController::getInstance() {
    if (!instance) {
        instance = new CameraController;
    }
    return instance;
}

CameraController::CameraController() {}

CameraController::CameraController(std::shared_ptr<MainWindow> mw) {
    mainWindow = mw;
}

void CameraController::setMainWindow(std::shared_ptr<MainWindow> mw) {
    mainWindow = mw;
}

void CameraController::addCamera(Camera camera) {
    cameras.push_back(camera);
}

void CameraController::deleteCamera(Camera camera) {
    cameras.remove(camera);
}

void CameraController::clearController() {
    cameras.clear();
}

void CameraController::updateObservations() {
    for (auto it = cameras.begin(); it != cameras.end(); ++it) {
        it->clearObservation();
        it->updateObservation();
    }
}