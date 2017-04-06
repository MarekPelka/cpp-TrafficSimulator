#include "CameraController.h"

CameraController* CameraController::instance = nullptr;

CameraController* CameraController::getInstance()
{
    if (!instance)
        instance = new CameraController;
    return instance;
}

CameraController::CameraController()
{

}

CameraController::CameraController(MainWindow * mw)
{
    mainWindow = mw;
}

void CameraController::setMainWindow(MainWindow * mw)
{
    mainWindow = mw;
}
