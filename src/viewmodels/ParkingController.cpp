#include "ParkingController.h"

ParkingController * ParkingController::instance = nullptr;

ParkingController::ParkingController() {
    std::srand(static_cast <unsigned int> (std::time(0)));
}

ParkingController * ParkingController::getInstance() {
    if (!instance)
        instance = new ParkingController;
    return instance;
}

void ParkingController::randomSpawnVehicle(double probability) {
    CityController * cityC = CityController::getInstance();
    MovementController *moveC = MovementController::getInstance();
    std::list<PNode> parkingList = cityC->getParkings();
    if (parkingList.size() < 2)
        return;
    for (auto parking : parkingList) {
        double random_value = std::rand();
        double roll = double(random_value / RAND_MAX);
        if (roll < PROBABILITY_SPAWN / probability) {
            // vehicle spawn
            double destination = std::rand() % 1000;
            destination = destination / 1000;
            int endNumber = static_cast <int> (round(destination * (parkingList.size() - 1)));
            std::list<PNode>::iterator it = parkingList.begin();
            std::advance(it, endNumber);
            if (it == parkingList.end())
                it = parkingList.begin();
            if (*it == parking) {
                std::advance(it, 1);
                if (it == parkingList.end())
                    it = parkingList.begin();
            }
            PNode end = *it;
            if (roll < (PROBABILITY_SPAWN / probability) * PERCENTAGE_OF_TRUCKS) {
                //spawn truck
                if (!cityC->findWay(parking, end).empty()) {
                    Vehicle truck(TRUCK, cityC->findWay(parking, end));
                    moveC->addVehicle(truck);
                }
            }
            else {
                //spawn car
                if (!cityC->findWay(parking, end).empty()) {
                    Vehicle car(CAR, cityC->findWay(parking, end));
                    moveC->addVehicle(car);
                }
            }
        }
    }
}

void ParkingController::randomSpawnPedestrian(double probability)
{
    CityController * cityC = CityController::getInstance();
    MovementController *moveC = MovementController::getInstance();
    std::list<PNode> parkingList = cityC->getParkings();
    if (parkingList.size() < 2)
        return;
    for (auto parking : parkingList) {
        double random_value = std::rand();
        double roll = double(random_value / RAND_MAX);
        if (roll < PROBABILITY_SPAWN / (probability*4)) {
            // pedestrian spawn
            double destination = std::rand() % 100;
            destination = destination / 100;
            int endNumber = static_cast <int> (round(destination * (parkingList.size() - 1)));
            std::list<PNode>::iterator it = parkingList.begin();
            std::advance(it, endNumber);
            if (it == parkingList.end())
                it = parkingList.begin();
            if (*it == parking) {
                std::advance(it, 1);
                if (it == parkingList.end())
                    it = parkingList.begin();
            }
            PNode end = *it;
            if (!cityC->findWay(parking, end).empty()) {
                Pedestrian ped(cityC->findWay(parking, end));
                moveC->addPedestrian(ped);
            }
        }
    }

}


