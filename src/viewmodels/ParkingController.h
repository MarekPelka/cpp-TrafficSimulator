/**
* \class ParkingController
* \ingroup viewmodels
* \details class controlling parkings and random spawning moving objects
* \author Micha³ Krzemiñski
* \author Marek Pelka
*/

#ifndef PARKINGCONTROLLER_H
#define PARKINGCONTROLLER_H
#include "CityController.h"
#include "MovementController.h"
#include <ctime>
#include <list>
#include <memory>
#include <math.h> 
class ParkingController {
public:
    //destructor
    void DescParkingController();
    ///singleton getInstance method
    static ParkingController* getInstance();
    /**generate random spawning vehicles between random parkings
    * \param probability
    */
    void randomSpawnVehicle(double probability);
    /**generate random spawning pedestrians between random parkings
    * \param probability
    */
    void randomSpawnPedestrian(double probability);
private:
    ///default constructor
    ParkingController();
    ///singleton instance pointer
    static ParkingController* instance;
};
#endif