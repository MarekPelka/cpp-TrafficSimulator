#ifndef VEHICLECONTROLLER_H
#define VEHICLECONTROLLER_H
#include "../models/Position.h"
#include "../models/Vehicle.h"
#include <list>
#include <memory>
//#include "../models/Street.h"
#include "CityController.h"

class Street;
typedef std::shared_ptr<Street> PStreet;

class VehicleController {
public:
	void addVehicle(Vehicle vehicle);
	void addVehicleToSwitch(Vehicle vehicle);
	void addPedestrian(Pedestrian ped);
	std::list<Vehicle> getVehicles();
	std::list<Pedestrian> getPedestrians();
	std::list<Vehicle> * getVehiclesToSwitch();
	void updatePositions(int interval);
	void clearController();

	static VehicleController* getInstance();
private:
	VehicleController();

	static VehicleController* instance;
	void updatePositionCallback(PStreet s, int arg);
	std::list<Vehicle> vehiclesToSwitch;
};
#endif