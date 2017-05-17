#ifndef VEHICLECONTROLLER_H
#define VEHICLECONTROLLER_H
#include "../models/Position.h"
#include "../models/Vehicle.h"
#include <list>
#include <memory>
#include "../models/Street.h"
#include "CityController.h"

class VehicleController {
public:
    void addVehicle(Vehicle vehicle);
    void addPedestrian(Pedestrian ped);
    std::list<Vehicle> getVehicles();
    std::list<Pedestrian> getPedestrians();
    void updatePositions(int interval);
    void clearController();

    static VehicleController* getInstance();
private:
    VehicleController();
    static VehicleController* instance;

    //std::list<Street> vehicles;
};
#endif