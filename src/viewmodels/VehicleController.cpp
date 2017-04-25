#include "VehicleController.h"

VehicleController* VehicleController::instance = nullptr;

VehicleController* VehicleController::getInstance() {
    if (!instance)
        instance = new VehicleController;
    return instance;
}

VehicleController::VehicleController() {}

VehicleController::VehicleController(std::shared_ptr<MainWindow> mw) {
    mainWindow = mw;
    vehicles = {};
}

void VehicleController::setMainWindow(std::shared_ptr<MainWindow> mw) {
    mainWindow = mw;
}

void VehicleController::addVehicle(Vehicle vehicle) {
    vehicles.push_back(vehicle);
}

void VehicleController::deleteVehicle(Vehicle vehicle) {
    for (std::list<Vehicle>::iterator iter = vehicles.begin(); iter != vehicles.end(); iter++) {
        if (*iter == vehicle) {
            vehicles.remove(vehicle);
            deleted = true;
            break;
        }
    }
}

std::list<Vehicle> VehicleController::getVehicles() {
    return vehicles;
}

void VehicleController::updatePositions(int interval) {
    for (std::list<Vehicle>::iterator iter = vehicles.begin(); iter != vehicles.end();) {
        iter->updatePosition(interval);
        if (deleted) {
            deleted = false;
            break;
        }
        else {
            ++iter;
        }
    }
    mainWindow->updateVehiclesViews();
}
