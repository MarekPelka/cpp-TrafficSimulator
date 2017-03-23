#include "VehicleController.h"

VehicleController* VehicleController::instance = nullptr;

VehicleController* VehicleController::getInstance()
{
	if (!instance)
		instance = new VehicleController;
	return instance;
}

VehicleController::VehicleController()
{

}

VehicleController::VehicleController(MainWindow * mw)
{
	mainWindow = mw;
	vehicles = {};
}

void VehicleController::setMainWindow(MainWindow * mw)
{
	mainWindow = mw;
}

void VehicleController::addVehicle(Vehicle vehicle)
{
	vehicles.push_back(vehicle);
}

std::list<Vehicle> VehicleController::getVehicles()
{
	return vehicles;
}

void VehicleController::updatePositions(int interval)
{
	std::list<Vehicle> temp;
	for(Vehicle veh : vehicles)
	{
		veh.updatePosition(interval);
		temp.push_back(veh);
		//tutaj position jest ladnie zupdatowane
		//widac tu jest lokalne a nie jest zupdatowana lista
	}
	//tutaj wraca do poprzedniej wartosci position po wyjsciu z fora
	vehicles = temp;
	mainWindow->updateVehiclesViews();
}
