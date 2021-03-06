#include "Camera.h"
#include "../viewmodels/CameraController.h"
#include "../viewmodels/MovementController.h"

int Camera::counter = 0;

Camera::Camera() : id(++counter) {
}

Camera::Camera(Position pos) {
    id = ++counter;
    position = pos;
    angle = 4 * right_angle; //omni-directional characteristic
    direction = NONE;
}

Camera::Camera(Position pos, int angl, Direction dir) {
    id = ++counter;
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
    MovementController *moveC = MovementController::getInstance();
    std::list<PVehicle> vehicles;
    vehicles = moveC->getVehicles();
    for (auto veh : vehicles) {
        if (veh) {
        double angl = getAngleBetweenPoints(position, veh->getPosition());
        if (checkIfInZone(angl)) {
            if (CameraController::getInstance()->checkIfBuilding(position, veh->getPosition())) {
                double distsqr = getDistanceBetweenPoints(position, veh->getPosition());

                int accuracy = 100;
                //CAMERA_PRECISION/(d^2)
                double distNoisiness = (CAMERA_PRECISION / distsqr) * accuracy;
                double result = rand() % accuracy;
                if (result < distNoisiness) {
                    observation.push_back(veh->getPosition().getCoordinates());
                }
                else {
                    //veh lost due to noises
                }
            }
        }

        }
    }
}

double Camera::getAngleBetweenPoints(Position p1, Position p2) {
    double angleRad = atan2(p2.y - p1.y, p2.x - p1.x);
    return angleRad * 2 * right_angle / M_PI;
}

bool Camera::checkIfInZone(double angl) {
    double border1 = 0, border2 = 0;
    switch (direction) {
    case S: {
        border1 = right_angle + (angle / 2);
        border2 = right_angle - (angle / 2);
        break;
    }
    case N: {
        border1 = -right_angle + (angle / 2);
        border2 = -right_angle - (angle / 2);
        break;
    }
    case W: {
        border1 = angle / 2;
        border2 = -(angle / 2);
        break;
    }
    case E: {
        border1 = 2 * right_angle + (angle / 2);
        border2 = 2 * right_angle - (angle / 2);
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

double Camera::getDistanceBetweenPoints(Position p1, Position p2) {
    return pow(abs(p1.x-p2.x), 2) + pow(abs(p1.y - p2.y), 2);
}

Position Camera::getPosition() {
	return position;
}

bool Camera::operator==(const Camera & v) {
    return position == v.position && angle == v.angle && direction == v.direction;
}