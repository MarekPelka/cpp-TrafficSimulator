#include <thread>
#include <vector>

#include "MovementController.h"

MovementController* MovementController::instance = nullptr;

MovementController* MovementController::getInstance() {
	if (!instance)
		instance = new MovementController;
	return instance;
}

MovementController::MovementController() {
	vehiclesToSwitch = std::list<Vehicle>();
}

std::list<Vehicle> * MovementController::getVehiclesToSwitch() {
	return &vehiclesToSwitch;
}

std::list<Pedestrian> * MovementController::getPedestriansToSwitch() {
    return &pedestriansToSwitch;
}

void MovementController::addVehicle(Vehicle vehicle) {
	if (auto spt = vehicle.getNodes().front().getStreetsIn().at(vehicle.getOrientation()).lock()) { // Has to be copied into a shared_ptr before usage	
		spt->addVehicleToStreet(vehicle);
	}
	//vehicles.push_back(vehicle);
}

void MovementController::addVehicleToSwitch(Vehicle vehicle) {
	vehiclesToSwitch.push_back(vehicle);
}

void MovementController::addPedestrianToSwitch(Pedestrian ped) {
    pedestriansToSwitch.push_back(ped);
}

void MovementController::addPedestrian(Pedestrian ped) {
	if (auto spt = ped.getNodes().front().getStreetsIn().at(ped.getOrientation()).lock()) { // Has to be copied into a shared_ptr before usage	
		spt->addPedestrianToStreet(ped);
	}
}

std::list<Vehicle> MovementController::getVehicles() {
	std::list<Vehicle> out;
	for (PStreet s : CityController::getInstance()->getStreets()) {
		std::vector<Vehicle> * temp = s->getVehicles();
		out.insert(out.end(), temp->begin(), temp->end());
	}
	return out;
}

std::list<Pedestrian> MovementController::getPedestrians() {
	std::list<Pedestrian> out;
	for (PStreet s : CityController::getInstance()->getStreets()) {
		std::vector<Pedestrian> * temp = s->getPedestrians();
		out.insert(out.end(), temp->begin(), temp->end());
	}
	return out;
}

void MovementController::updatePositions(int interval) {

	//boost::thread_group threads;
	std::vector<std::thread> threadsVC;

	for (PStreet s : CityController::getInstance()->getStreets()) {
		std::pair<PStreet, int> args(s, interval);
		
		if (!s->getVehicles()->empty() || !s->getPedestrians()->empty()) {
			threadsVC.push_back(std::thread(&MovementController::updatePositionCallback, this, s, interval));
		}
	}
	for (int i = 0; i < threadsVC.size(); ++i) {
		threadsVC.at(i).join();
	}

	for (Vehicle v : vehiclesToSwitch) {
		v.getStreetToSwitch()->addVehicleToStreet(v);
	}
	vehiclesToSwitch.clear();

    for (Pedestrian p : pedestriansToSwitch) {
        p.getStreetToSwitch()->addPedestrianToStreet(p);
    }
    pedestriansToSwitch.clear();
}

void MovementController::updatePositionCallback(PStreet s, int arg) {
	s->updatePositions(arg);
}

void MovementController::clearController() {
	for (PStreet s : CityController::getInstance()->getStreets()) {
		s->getVehicles()->clear();
	}
    for (PStreet s : CityController::getInstance()->getStreets()) {
        s->getPedestrians()->clear();
    }
}
