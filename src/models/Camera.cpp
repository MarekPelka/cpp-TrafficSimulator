#include "Camera.h"

Camera::Camera() {
}

Camera::Camera(Position pos) {
    position = pos;
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

std::map <int, int> Camera::getView() {
    std::map <int, int> observation;
    //TODO
    return observation;
}
