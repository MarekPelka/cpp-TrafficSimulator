/**
* \class MovementController
* \ingroup viewmodels
* \details class controlling moving objects and updating their positions
* \author Micha³ Krzemiñski
* \author Marek Pelka
*/

#ifndef MOVEMENTCONTROLLER_H
#define MOVEMENTCONTROLLER_H
#include "../models/Position.h"
#include "../models/Vehicle.h"
#include <list>
#include <memory>
#include "CityController.h"

class Street;
typedef std::shared_ptr<Street> PStreet;
typedef std::shared_ptr<Vehicle> PVehicle;
typedef std::shared_ptr<Pedestrian> PPedestrian;

class MovementController {
public:
    /**add vehicle object to proper street collection vehOnStreet
    * \param vehicle
    */
	void addVehicle(Vehicle vehicle);
    /**add vehicle object to vehiclesToSwitch list
    * \param vehicle
    */
	void addVehicleToSwitch(Vehicle vehicle);
    /**add pedestrian object to proper street collection pedOnStreet
    * \param pedestrian
    */
	void addPedestrian(Pedestrian ped);
    /**add pedestrian object to pedestriansToSwitch list
    * \param pedestrian
    */
    void addPedestrianToSwitch(Pedestrian ped);
    ///return all vehicles
	std::list<PVehicle> getVehicles();
    ///return all pedestrians
	std::list<PPedestrian> getPedestrians();
    ///return all vehicles that have to change street
	std::list<PVehicle> * getVehiclesToSwitch();
    ///return all pedestrians that have to change street
    std::list<PPedestrian> * getPedestriansToSwitch();
    ///update positions of all moving objects
	void updatePositions(int interval, bool evenCare = true);
    ///clear controller
	void clearController();
    ///singleton getInstance method
	static MovementController* getInstance();
private:
    ///default constructor
	MovementController();
    ///singleton instance pointer
	static MovementController* instance;
    /**callback for updating positions of all objects on one street
    * \param street
    * \param interval
    */
	void updatePositionCallback(PStreet s, int arg, bool evenCare);
    ///colection of all vehicles that have to change street
	std::list<PVehicle> vehiclesToSwitch;
    ///colection of all pedestrians that have to change street
    std::list<PPedestrian> pedestriansToSwitch;
};
#endif