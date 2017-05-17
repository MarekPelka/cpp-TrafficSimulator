#include "VehicleController.h"

VehicleController* VehicleController::instance = nullptr;

VehicleController* VehicleController::getInstance() {
    if (!instance)
        instance = new VehicleController;
    return instance;
}

VehicleController::VehicleController() {}

void VehicleController::addVehicle(Vehicle vehicle) {
	if (auto spt = vehicle.getNodes().front().getStreetsIn().at(vehicle.getOrientation()).lock()) { // Has to be copied into a shared_ptr before usage	
		spt->addVehicleToStreet(vehicle);
	}
    //vehicles.push_back(vehicle);
}

void VehicleController::addPedestrian(Pedestrian ped) {
    if (auto spt = ped.getNodes().front().getStreetsIn().at(ped.getOrientation()).lock()) { // Has to be copied into a shared_ptr before usage	
        spt->addPedestrianToStreet(ped);
    }
}

std::list<Vehicle> VehicleController::getVehicles() {
	std::list<Vehicle> out;
	for (PStreet s : CityController::getInstance()->getStreets()) {
		std::vector<Vehicle> * temp = s->getVehicles();
		out.insert(out.end(), temp->begin(), temp->end());
	}
	return out;
}

std::list<Pedestrian> VehicleController::getPedestrians() {
    std::list<Pedestrian> out;
    for (PStreet s : CityController::getInstance()->getStreets()) {
        std::vector<Pedestrian> * temp = s->getPedestrians();
        out.insert(out.end(), temp->begin(), temp->end());
    }
    return out;
}

void VehicleController::updatePositions(int interval) {
    //for (auto iter = vehicles.begin(); iter != vehicles.end();) {
    //    if (iter->updatePosition(interval)) {
    //        ++iter;
    //    }
    //    else {
    //        //delete vehicle
    //        //erase this vehicle from list
    //        iter = vehicles.erase(iter);
    //    }
    //}
	for (PStreet s : CityController::getInstance()->getStreets()) {
		s->updatePositions(interval);
	}
    //mainWindow->updateVehiclesViews();
}

void VehicleController::clearController() {
	for (PStreet s : CityController::getInstance()->getStreets()) {
		s->getVehicles()->clear();
	}
}
