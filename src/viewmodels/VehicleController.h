#pragma once
#include "../models/Position.h"
#include "../models/Vehicle.h"
#include "MainWindow.h"
#include <list>
#include <memory>

class VehicleController {
public:
    void setMainWindow(std::shared_ptr<MainWindow> mw);
    void addVehicle(Vehicle vehicle);
    void deleteVehicle(Vehicle vehicle);
    std::list<Vehicle> getVehicles();
    void updatePositions(int interval);

    static VehicleController* getInstance();
private:
    VehicleController();
    VehicleController(std::shared_ptr<MainWindow> mainWindow);
    static VehicleController* instance;

    std::shared_ptr<MainWindow> mainWindow;
    std::list<Vehicle> vehicles;
    bool deleted = false;
};
