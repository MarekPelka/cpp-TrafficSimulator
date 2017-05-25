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

void CameraController::writeToFile(std::string name) {
    file.open(name, std::ios::app | std::ios::ate);
    time_t now = time(0);
    if (file.is_open()) {
        for (auto it = cameras.begin(); it != cameras.end(); ++it) {
            std::list<std::pair<int, int>> temp = it->getView();
            if (!temp.empty()) {
                file << "CameraID: ";
                file << it->id;
                file << " ";
                file << "Timestamp: ";
				char str[26];
                file << ctime_s(str, sizeof(str), &now);
                for (auto iter = temp.begin(); iter != temp.end(); ++iter) {
                    file << iter->first;
                    file << " ";
                    file << iter->second;
                    file << "\n";
                }
            }
        }
        file.close();
    }
}

void CameraController::writeToDatabase() {
    for (auto it = cameras.begin(); it != cameras.end(); ++it) {
        std::list<std::pair<int, int>> temp = it->getView();
        if (!temp.empty()) {
            for (auto iter = temp.begin(); iter != temp.end(); ++iter) {
                //TODO timestamp
                SqlConnector::getInstance()->insert(it->id, "######", iter->first, iter->second);
            }
        }
    }
}

bool CameraController::checkIfBuilding(Position p1, Position p2) {
    for (auto building : getBuildings()) {
        //extending lines with 1px to cover corners
        if (LineIntersectsLine(p1, p2, Position(building.position.x -1, building.position.y), Position(building.position.x + BUILDING_SIZE + 1, building.position.y)) ||
            LineIntersectsLine(p1, p2, Position(building.position.x, building.position.y - 1), Position(building.position.x, building.position.y + BUILDING_SIZE + 1)) ||
            LineIntersectsLine(p1, p2, Position(building.position.x + BUILDING_SIZE, building.position.y + BUILDING_SIZE + 1), Position(building.position.x + BUILDING_SIZE, building.position.y - 1)) ||
            LineIntersectsLine(p1, p2, Position(building.position.x + BUILDING_SIZE + 1, building.position.y + BUILDING_SIZE), Position(building.position.x -1, building.position.y + BUILDING_SIZE))) {
            return false;
        }
    }
    return true;
}

bool CameraController::LineIntersectsLine(Position p1, Position p2, Position q1, Position q2) {
    double a = (((q1.x - p1.x)*(p2.y - p1.y)) - ((q1.y - p1.y)*(p2.x - p1.x)));
    double b = (((q2.x - p1.x)*(p2.y - p1.y) - (q2.y - p1.y)*(p2.x - p1.x)));
    double c = (((p1.x - q1.x)*(q2.y - q1.y) - (p1.y - q1.y)*(q2.x - q1.x)));
    double d = (((p2.x - q1.x)*(q2.y - q1.y) - (p2.y - q1.y)*(q2.x - q1.x)));
    if((a * b < 0) && (c * d < 0)) {
        return true;
    }
    else {
        return false;
    }
}