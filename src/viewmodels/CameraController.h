#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H
#include "../models/Building.h"
#include "../models/Camera.h"
#include "../models/SqlConnector.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <list>
#include <memory>
#include <thread>
//#include <windows.h>

class CameraController {
public:
    static CameraController* getInstance();
    void addCamera(Camera camera);
    void addBuilding(Building building);
    void deleteCamera(Camera camera);
    void deleteBuilding(Building building);
    void clearController();
    void updateObservations();
    bool checkIfBuilding(Position p1, Position p2);
    bool LineIntersectsLine(Position p1, Position p2, Position q1, Position q2);
    std::list<Camera> getCameras();
    std::list<Building> getBuildings();
    void writeToFile(std::string name);
    void writeToDatabase();

private:
    CameraController();
    static CameraController* instance;

    std::list<Camera> cameras;
    std::list<Building> buildings;
    std::ofstream file;
};
#endif