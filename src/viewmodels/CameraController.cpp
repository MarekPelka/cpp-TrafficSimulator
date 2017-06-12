#include "CameraController.h"

CameraController* CameraController::instance = nullptr;

CameraController* CameraController::getInstance() {
    if (!instance) {
        instance = new CameraController;
        //connect to sqlite database
        bool status = SqlConnector::getInstance()->connect();
        CameraController::getInstance()->insertType = status;
    }
    return instance;
}

CameraController::CameraController() {
    buildings = {};
    cameras = {};
}

void CameraController::DescCameraController() {
    if (instance) {
        buildings.clear();
        cameras.clear();
        delete instance;
    }
}

void CameraController::addCamera(Camera camera) {
	if(camera.getDirection() != NONE)
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
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(p);
    file.open(name, std::ios::app | std::ios::ate);
    if (file.is_open()) {
        for (auto it = cameras.begin(); it != cameras.end(); ++it) {
            std::list<std::pair<int, int>> temp = it->getView();
            if (!temp.empty()) {
                file << "CameraID: ";
                file << it->id;
                file << " ";
                file << "Timestamp: ";
                file << std::ctime(&t);
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
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(p);
    for (auto it = cameras.begin(); it != cameras.end(); ++it) {
        std::list<std::pair<int, int>> temp = it->getView();
        if (!temp.empty()) {
            for (auto iter = temp.begin(); iter != temp.end(); ++iter) {
                SqlConnector::getInstance()->insert(it->id, std::ctime(&t), iter->first, iter->second);
            }
        }
    }
}

bool CameraController::getInsertType() {
    return insertType;
}

bool CameraController::checkIfBuilding(Position p1, Position p2) {
    for (auto building : getBuildings()) {
        //extending lines with 1px to cover corners
        if (LineIntersectsLine(p1, p2, Position(building.position.x -1, building.position.y), Position(building.position.x + 2 * FULL_STREET_WIDTH + 1, building.position.y)) ||
            LineIntersectsLine(p1, p2, Position(building.position.x, building.position.y - 1), Position(building.position.x, building.position.y + 2 * FULL_STREET_WIDTH + 1)) ||
            LineIntersectsLine(p1, p2, Position(building.position.x + 2 * FULL_STREET_WIDTH, building.position.y + 2 * FULL_STREET_WIDTH + 1), Position(building.position.x + 2 * FULL_STREET_WIDTH, building.position.y - 1)) ||
            LineIntersectsLine(p1, p2, Position(building.position.x + 2 * FULL_STREET_WIDTH + 1, building.position.y + 2 * FULL_STREET_WIDTH), Position(building.position.x -1, building.position.y + 2 * FULL_STREET_WIDTH))) {
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