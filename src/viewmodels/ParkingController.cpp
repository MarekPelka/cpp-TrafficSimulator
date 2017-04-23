#include "ParkingController.h"

ParkingController * ParkingController::instance = nullptr;

ParkingController::ParkingController()
{
	std::srand(std::time(0));
}

ParkingController * ParkingController::getInstance()
{
	if (!instance)
		instance = new ParkingController;
	return instance;
}

void ParkingController::randomSpawnVechicle(double probability)
{
	CityController * cityC = CityController::getInstance();
	VehicleController *vehC = VehicleController::getInstance();
	std::list<Node*> parkingList = cityC->getParkings();
	if (parkingList.size() < 2)
		return;
	for (auto parking : parkingList) {
		double random_value = std::rand();
		double roll = double (random_value / RAND_MAX);
		if (roll < PROBABILITY_SPAWN / probability) {
			// vechicle spawn
			double destination = std::rand() % 1000;
			destination = destination / 1000;
			int endNumber = round(destination * (parkingList.size() - 1));
			std::list<Node *>::iterator it = parkingList.begin();
			std::advance(it, endNumber);
			if (it == parkingList.end())
				it = parkingList.begin();
			if (*it == parking) {
				std::advance(it, 1);
				if (it == parkingList.end())
					it = parkingList.begin();
			}
			Node * end = *it;
			if (roll < (PROBABILITY_SPAWN / probability) * PERCENTAGE_OF_TRUCKS) {
				//spawn truck
				if (!cityC->findWay(parking, end).empty())
				{
					Vehicle truck(TRUCK, cityC->findWay(parking, end));
					vehC->addVehicle(truck);
				}
			}
			else {
				//spawn car
				if (!cityC->findWay(parking, end).empty())
				{
					Vehicle car(CAR, cityC->findWay(parking, end));
					vehC->addVehicle(car);
				}
			}
		}
	}
}


