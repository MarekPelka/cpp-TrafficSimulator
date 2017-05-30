#ifndef MOVEMENTCONTROLLER_H
#define MOVEMENTCONTROLLER_H
#include "../models/Position.h"
#include "../models/Vehicle.h"
#include <list>
#include <memory>
#include "CityController.h"

class Street;
typedef std::shared_ptr<Street> PStreet;

class MovementController {
public:
	void addVehicle(Vehicle vehicle);
	void addVehicleToSwitch(Vehicle vehicle);
	void addPedestrian(Pedestrian ped);
    void addPedestrianToSwitch(Pedestrian ped);
	std::list<Vehicle> getVehicles();
	std::list<Pedestrian> getPedestrians();
	std::list<Vehicle> * getVehiclesToSwitch();
    std::list<Pedestrian> * getPedestriansToSwitch();
	void updatePositions(int interval);
	void clearController();

	static MovementController* getInstance();
private:
	MovementController();

	static MovementController* instance;
	void updatePositionCallback(PStreet s, int arg);
	std::list<Vehicle> vehiclesToSwitch;
    std::list<Pedestrian> pedestriansToSwitch;
};
#endif