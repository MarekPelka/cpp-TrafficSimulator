#include "CameraController.h"

CameraController* CameraController::instance = nullptr;

CameraController* CameraController::getInstance() {
    if (!instance) {
        instance = new CameraController;
    }
    return instance;
}

CameraController::CameraController() {}

void CameraController::addCamera(Camera camera) {
    cameras.push_back(camera);
}

void CameraController::deleteCamera(Camera camera) {
    cameras.remove(camera);
}

void CameraController::addBuilding(Building building) {
    buildings.push_back(building);
}

void CameraController::deleteBuilding(Building building) {
    buildings.remove(building);
}

void CameraController::clearController() {
    cameras.clear();
    buildings.clear();
}

void CameraController::updateObservations() {
    for (auto it = cameras.begin(); it != cameras.end(); ++it) {
        it->clearObservation();
        it->updateObservation();
    }
}

std::list<Camera> CameraController::getCameras() {
    return cameras;
}

std::list<Building> CameraController::getBuildings() {
    return buildings;
}