#pragma once
#include "CityController.h"
#include "VehicleController.h"
#include <ctime>
#include <list>
#include <memory>
#include <math.h> 
class ParkingController {
	//typedef std::shared_ptr<Parking> PParking;
public:
	static ParkingController* getInstance();

	void randomSpawnVechicle(double probability);

private:
	ParkingController();
	static ParkingController* instance;
	//std::list<PParking> parkings;
};