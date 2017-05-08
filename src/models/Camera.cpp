#include "Camera.h"
#include "../viewmodels/CameraController.h"
#include "../viewmodels/VehicleController.h"

Camera::Camera() {
}

Camera::Camera(Position pos) {
    position = pos;
    angle = 360; //omni-directional characteristic
    direction = NONE;
}

Camera::Camera(Position pos, int angl, Direction dir) {
    position = pos;
    angle = angl;
    direction = dir;
}

void Camera::setAngle(int angl) {
    angle = angl;
}

int Camera::getAngle() {
    return angle;
}

void Camera::setDirection(Direction dir) {
    direction = dir;
}

Direction Camera::getDirection() {
    return direction;
}

std::list<std::pair<int, int>> Camera::getView() {
    return observation;
}

void Camera::clearObservation() {
    observation.clear();
}

void Camera::updateObservation() {
    VehicleController *vehC = VehicleController::getInstance();
    std::list<Vehicle> vehicles = vehC->getVehicles();
    for (auto veh : vehicles) {
        double angl = getAngleBetweenPoints(position, veh.getPosition());
        if (checkIfInZone(angl)) {
            if (checkIfBuilding(position, veh.getPosition())) {
                double distsqr = getDistanceBetweenPoints(position, veh.getPosition());

                int accuracy = 100;
                //prawo odwrotnych kwadratów CAMERA_PRECISION/(d^2)
                double distNoisiness = (CAMERA_PRECISION / distsqr) * accuracy;
                double result = rand() % accuracy;
                if (result < distNoisiness) {
                    observation.push_back(veh.getPosition().getCoordinates());
                }
                else {
                    //veh lost due to noises
                }
            }
        }
    }
}

double Camera::getAngleBetweenPoints(Position p1, Position p2) {
    double angleRad = atan2(p2.y - p1.y, p2.x - p1.x);
    return angleRad * 180 / M_PI;
}

bool Camera::checkIfInZone(double angl) {
    double border1 = 0, border2 = 0;
    switch (direction) {
    case N: {
        border1 = 90 + (angle / 2);
        border2 = 90 - (angle / 2);
        break;
    }
    case S: {
        border1 = -90 + (angle / 2);
        border2 = -90 - (angle / 2);
        break;
    }
    case E: {
        border1 = angle / 2;
        border2 = -(angle / 2);
        break;
    }
    case W: {
        border1 = 180 + (angle / 2);
        border2 = 180 - (angle / 2);
        break;
    }
    case NONE: {
        return true;
    }
    default:
        break;
    }
    if (angl <= border1 && angl >= border2) {
        return true;
    }
    else {
        return false;
    }
}

bool Camera::checkIfBuilding(Position p1, Position p2)
{
    for (auto building : CameraController::getInstance()->getBuildings()) {
        if (LineIntersectsLine(p1, p2, building.position, Position(building.position.x + BUILDING_SIZE, building.position.y)) ||
            LineIntersectsLine(p1, p2, building.position, Position(building.position.x, building.position.y - BUILDING_SIZE)) ||
            LineIntersectsLine(p1, p2, Position(building.position.x + BUILDING_SIZE, building.position.y - BUILDING_SIZE), Position(building.position.x + BUILDING_SIZE, building.position.y)) ||
            LineIntersectsLine(p1, p2, Position(building.position.x + BUILDING_SIZE, building.position.y - BUILDING_SIZE), Position(building.position.x, building.position.y - BUILDING_SIZE))) {
            return false;
        }
    }
    return true;
}

bool Camera::LineIntersectsLine(Position p1, Position p2, Position q1, Position q2) {
        return (((q1.x-p1.x)*(p2.y-p1.y) - (q1.y-p1.y)*(p2.x-p1.x))
            * ((q2.x-p1.x)*(p2.y-p1.y) - (q2.y-p1.y)*(p2.x-p1.x)) < 0)
            &&
           (((p1.x-q1.x)*(q2.y-q1.y) - (p1.y-q1.y)*(q2.x-q1.x))
            * ((p2.x-q1.x)*(q2.y-q1.y) - (p2.y-q1.y)*(q2.x-q1.x)) < 0);
}

double Camera::getDistanceBetweenPoints(Position p1, Position p2) {
    return pow(abs(p1.x-p2.x), 2) + pow(abs(p1.y - p2.y), 2);
}

bool Camera::operator==(const Camera & v) {
    return position == v.position && angle == v.angle && direction == v.direction;
}