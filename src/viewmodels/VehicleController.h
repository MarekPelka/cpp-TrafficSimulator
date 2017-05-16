#ifndef VEHICLECONTROLLER_H
#define VEHICLECONTROLLER_H
#include "../models/Position.h"
#include "../models/Vehicle.h"
//#include "MainWindow.h"
#include <list>
#include <memory>
#include "../models/Street.h"
#include "CityController.h"

class VehicleController {
public:
    //void setMainWindow(std::shared_ptr<MainWindow> mw);
    void addVehicle(Vehicle vehicle);
    std::list<Vehicle> getVehicles();
    void updatePositions(int interval);
    void clearController();

    static VehicleController* getInstance();
private:
    VehicleController();
    static VehicleController* instance;

    //std::shared_ptr<MainWindow> mainWindow;
    //std::list<Street> vehicles;
};
#endif