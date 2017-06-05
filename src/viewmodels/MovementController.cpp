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
    vehiclesToSwitch = {};
    pedestriansToSwitch = {};
}

void MovementController::DescMovementController() {
    if (instance) {
        vehiclesToSwitch.clear();
        pedestriansToSwitch.clear();
        delete instance;
    }
}

std::list<PVehicle> * MovementController::getVehiclesToSwitch() {
	return &vehiclesToSwitch;
}

std::list<PPedestrian> * MovementController::getPedestriansToSwitch() {
    return &pedestriansToSwitch;
}

void MovementController::addVehicle(Vehicle vehicle) {
	if (auto spt = vehicle.getNodes().front().getStreetsIn().at(vehicle.getOrientation()).lock()) {
		spt->addVehicleToStreet(vehicle);
	}
}

void MovementController::addVehicleToSwitch(Vehicle vehicle) {
	vehiclesToSwitch.push_back(std::make_shared<Vehicle>(vehicle));
}

void MovementController::addPedestrianToSwitch(Pedestrian ped) {
    pedestriansToSwitch.push_back(std::make_shared<Pedestrian>(ped));
}

void MovementController::addPedestrian(Pedestrian ped) {
	if (auto spt = ped.getNodes().front().getStreetsIn().at(ped.getOrientation()).lock()) {
		spt->addPedestrianToStreet(ped);
	}
}

std::list<PVehicle> MovementController::getVehicles() {
	std::list<PVehicle> out;
	for (PStreet s : CityController::getInstance()->getStreets()) {
		std::vector<PVehicle> * temp = s->getVehicles();
		out.insert(out.end(), temp->begin(), temp->end());
	}
	return out;
}

std::list<PPedestrian> MovementController::getPedestrians() {
	std::list<PPedestrian> out;
	for (PStreet s : CityController::getInstance()->getStreets()) {
		std::vector<PPedestrian> * temp = s->getPedestrians();
		out.insert(out.end(), temp->begin(), temp->end());
	}
	return out;
}

void MovementController::updatePositions(int interval, bool evenCare) {

	std::vector<std::thread> threadsVC;

	for (PStreet s : CityController::getInstance()->getStreets()) {
		std::pair<PStreet, int> args(s, interval);
		
		if (!s->getVehicles()->empty() || !s->getPedestrians()->empty()) {
			threadsVC.push_back(std::thread(&MovementController::updatePositionCallback, this, s, interval, evenCare));
		}
	}
	for (size_t i = 0; i < threadsVC.size(); ++i) {
		threadsVC.at(i).join();
	}

	for (auto v : vehiclesToSwitch) {
		v->getStreetToSwitch()->addVehicleToStreet(*v);
	}
	vehiclesToSwitch.clear();

    for (PPedestrian p : pedestriansToSwitch) {
        p->getStreetToSwitch()->addPedestrianToStreet(*p);
    }
    pedestriansToSwitch.clear();
}

void MovementController::updatePositionCallback(PStreet s, int arg, bool evenCare) {
	s->updatePositions(arg, evenCare);
}

void MovementController::clearController() {
	for (PStreet s : CityController::getInstance()->getStreets()) {
		s->getVehicles()->clear();
	}
    for (PStreet s : CityController::getInstance()->getStreets()) {
        s->getPedestrians()->clear();
    }
}
