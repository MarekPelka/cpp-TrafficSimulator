#include "VehicleController.h"

VehicleController* VehicleController::instance = nullptr;

VehicleController* VehicleController::getInstance() {
    if (!instance)
        instance = new VehicleController;
    return instance;
}

VehicleController::VehicleController() {}

void VehicleController::setMainWindow(std::shared_ptr<MainWindow> mw) {
    mainWindow = mw;
}

void VehicleController::addVehicle(Vehicle vehicle) {
    vehicles.push_back(vehicle);
}

std::list<Vehicle> VehicleController::getVehicles() {
    return vehicles;
}

void VehicleController::updatePositions(int interval) {
    for (auto iter = vehicles.begin(); iter != vehicles.end();) {
        if (iter->updatePosition(interval)) {
            ++iter;
        }
        else {
            //delete vehicle
            //erase this vehicle from list
            iter = vehicles.erase(iter);
        }
    }
    mainWindow->updateVehiclesViews();
}

void VehicleController::clearController() {
    vehicles.clear();
}
