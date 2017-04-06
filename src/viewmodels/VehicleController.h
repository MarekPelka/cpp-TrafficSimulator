#pragma once
#include "src/models/Position.h"
#include "src/models/Vehicle.h"
#include "MainWindow.h"
#include <list>
#include "boost/regex.hpp"

class VehicleController
{
    public:
        void setMainWindow(MainWindow *mw);
        void addVehicle(Vehicle vehicle);
        void deleteVehicle(Vehicle vehicle);
        std::list<Vehicle> getVehicles();
        void updatePositions(int interval);

        static VehicleController* getInstance();
    private:
        VehicleController();
        VehicleController(MainWindow *mw);
        static VehicleController* instance;

        MainWindow *mainWindow;
        std::list<Vehicle> vehicles;
        bool deleted = false;
};
