//#include <boost/thread/thread.hpp>
//#include <boost/bind.hpp>
//#include <boost/core/ref.hpp>

#include <thread>
#include <vector>

#include "VehicleController.h"

VehicleController* VehicleController::instance = nullptr;

VehicleController* VehicleController::getInstance() {
	if (!instance)
		instance = new VehicleController;
	return instance;
}

VehicleController::VehicleController() {
	vehiclesToSwitch = std::list<Vehicle>();
}

std::list<Vehicle> * VehicleController::getVehiclesToSwitch() {
	return &vehiclesToSwitch;
}

void VehicleController::addVehicle(Vehicle vehicle) {
	if (auto spt = vehicle.getNodes().front().getStreetsIn().at(vehicle.getOrientation()).lock()) { // Has to be copied into a shared_ptr before usage	
		spt->addVehicleToStreet(vehicle);
	}
	//vehicles.push_back(vehicle);
}

void VehicleController::addVehicleToSwitch(Vehicle vehicle) {
	vehiclesToSwitch.push_back(vehicle);
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

	//boost::thread_group threads;
	std::vector<std::thread> threadsVC;

	for (PStreet s : CityController::getInstance()->getStreets()) {
		std::pair<PStreet, int> args(s, interval);
		//threads.create_thread(boost::bind(&VehicleController::updatePositionCallback, boost::cref(s), boost::cref(interval)));
		//threads.add_thread(new boost::thread(&VehicleController::updatePositionCallback, this, s, interval));
		threadsVC.push_back(std::thread(&VehicleController::updatePositionCallback, this, s, interval));
	}
	for (int i = 0; i < threadsVC.size(); ++i) {
		//if (threadsVC.at(i).joinable())
		threadsVC.at(i).join();
	}
	for (Vehicle v : vehiclesToSwitch) {
		v.getStreetToSwitch()->addVehicleToStreet(v);
	}
	//getVehiclesToSwitch().clear();
    if (vehiclesToSwitch.size() != 0) {
        auto deleteIterator = vehiclesToSwitch.begin();
        while (deleteIterator != vehiclesToSwitch.end()) {
            deleteIterator = vehiclesToSwitch.erase(deleteIterator);
        }
    }
	//s->addVehicleToStreet(vec.front());
	//threadsVC.back().join();
}

void VehicleController::updatePositionCallback(PStreet s, int arg) {
	s->updatePositions(arg);
	//args.first->updatePositions(args.second);
}

void VehicleController::clearController() {
	for (PStreet s : CityController::getInstance()->getStreets()) {
		s->getVehicles()->clear();
	}
}
