#pragma once
#include "Position.h"
#include "Vehicle.h"
#include "MainWindow.h"
#include <list>
#include <QDebug>
#include <boost/signals2/signal.hpp>
#include <boost/bind.hpp>

class VehicleController
{
    public:
        void setMainWindow(MainWindow *mw);
        void addVehicle(Vehicle vehicle);
        void deleteVehicle(Vehicle vehicle);
        std::list<Vehicle> getVehicles();
        void updatePositions(int interval);

        boost::signals2::signal<void(std::list<QRect*>)> sigRenderVehicles;
        static VehicleController* getInstance();
    private:
        VehicleController();
        VehicleController(MainWindow *mw);
        static VehicleController* instance;

        MainWindow *mainWindow;
        std::list<Vehicle> vehicles;
        bool deleted = false;
};
