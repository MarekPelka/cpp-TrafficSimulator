#include "VehicleController.h"

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

void VehicleController::addVehicle(Vehicle *vehicle)
{
	vehicles.push_back(vehicle);
}

std::list<Vehicle*>* VehicleController::getVehicles()
{
	return &vehicles;
}

std::list<QRect*> VehicleController::getVehiclesGraphics()
{
	std::list<QRect*> out = {};
	for (Vehicle* v : vehicles)
	{
		out.push_back(new QRect(v->getPosition().x, v->getPosition().y,
			v->getPosition().x + carWidth, v->getPosition().y + carWidth));
	}
	return out;
}
