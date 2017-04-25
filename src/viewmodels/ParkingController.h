#pragma once
#include "CityController.h"
#include "VehicleController.h"
#include <ctime>
#include <list>
#include <memory>
#include <math.h> 
class ParkingController {
public:
    static ParkingController* getInstance();
    void randomSpawnVechicle(double probability);
private:
    ParkingController();
    static ParkingController* instance;
    //TO CONSIDER
    //std::list<PParking> parkings;
};