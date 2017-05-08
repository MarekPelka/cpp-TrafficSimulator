#pragma once
#include "../models/Building.h"
#include "../models/Camera.h"
#include <list>
#include <memory>
#include <thread>
#include <windows.h>

class CameraController {
public:
    static CameraController* getInstance();
    void addCamera(Camera camera);
    void addBuilding(Building building);
    void deleteCamera(Camera camera);
    void deleteBuilding(Building building);
    void clearController();
    void updateObservations();
    std::list<Camera> getCameras();
    std::list<Building> getBuildings();

private:
    CameraController();
    static CameraController* instance;

    std::list<Camera> cameras;
    std::list<Building> buildings;
};
